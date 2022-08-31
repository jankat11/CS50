import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    try:
        table = db.execute("SELECT * FROM summ WHERE id = ? ORDER BY symbol", session["user_id"])
        for i in range(len(table)):
            table[i]["price"] = lookup(table[i]["symbol"])["price"]
        currentcash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        total = 0
        for tab, shr in zip(table, table):
            total = total + tab["price"] * shr["share"]

        username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
        return render_template("index.html", table=table, currentcash=currentcash, total=total, username=username.upper())
    except:
        return render_template("succes.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        shares = request.form.get("shares")
        try:
            buy = request.form.get("symbol").upper()
            lookup(buy)["name"]
        except:
            return apology("invalid symbol", 400)

        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        elif not request.form.get("shares"):
            return apology("must provide share amount", 403)

        try:
            shares = int(shares)
            if shares < 1:
                return apology("must correct share amount", 400)
        except:
            return apology("must correct share amount", 400)

        symbol = request.form.get("symbol").upper()
        name = lookup(symbol)["name"]
        price = float(lookup(symbol)["price"])
        totalprice = price * shares
        currentcash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if float(currentcash) < float(totalprice):
            return apology("insufficent cash:(", 400)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", float(currentcash) - float(totalprice), session["user_id"])
        ids = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        for id in ids:
            db.execute("INSERT INTO buy (id, symbol, name, share, price) VALUES(?, ?, ?, ?, ?)",
                       id["id"], symbol, name, shares, price)

        sharess = []
        s = db.execute("SELECT share FROM buy WHERE symbol = ? AND id = ?", symbol, session["user_id"])
        for share in s:
            sharess.append(share["share"])
        totalshare = int(sum(sharess))
        porto = db.execute("SELECT symbol FROM summ WHERE symbol = ? AND id = ?", symbol, session["user_id"])

        if not porto:
            db.execute("INSERT INTO summ (symbol, name, share, price, id) VALUES(?, ?, ?, ?, ?)",
                       symbol, name, totalshare, price, session["user_id"])
        else:
            db.execute("UPDATE summ SET share = ?, price = ? WHERE id = ? AND symbol = ?",
                       totalshare, price, session["user_id"], symbol)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    table = db.execute("SELECT symbol, name, share, price, no FROM buy WHERE id = ? ORDER BY no DESC", session["user_id"])

    return render_template("history.html", table=table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["name"] = rows[0]["username"]
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # Check if the symbol entered exist / if exists render cost, else return apology
        try:
            symbol = request.form.get("symbol").upper()
            name = lookup(symbol)["name"]
            price = lookup(symbol)["price"]
            costs = "current cost:"
            return render_template("quote.html", name=name, price=usd(price), costs=costs)
        except:
            return apology("invalid symbol", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        sameusers = []
        allusers = db.execute("SELECT username FROM users")
        for user in allusers:
            sameusers.append(user["username"])

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure username is not already exists
        elif username in sameusers:
            return apology("this username already exists", 400)

        # Password confrmation check
        elif password != confirmation:
            return apology("passwords did not match", 400)

        # Submit registration
        hash = generate_password_hash(password, method="pbkdf2:sha256", salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    try:
        stocks = db.execute("SELECT * FROM summ WHERE id = ? ORDER BY symbol", session["user_id"])
    except:
        return apology("No stock to sell", 400)
    if request.method == "POST":
        sharr = request.form.get("shares")
        symbol = request.form.get("symbol")

        if not sharr:
            return apology("must enter share amount", 400)
        elif not symbol:
            return apology("must enter valid symbol", 400)
        try:
            sharr = int(sharr)
            if sharr < 1:
                return apology("must correct share amount", 400)
        except:
            return apology("must correct share amount", 400)

        for i in range(len(stocks)):
            stocks[i]["price"] = lookup(stocks[i]["symbol"])["price"]
            if stocks[i]["symbol"] == symbol.upper():
                price = int(stocks[i]["price"])
                name = stocks[i]["name"]

        shares = int(db.execute("SELECT share FROM summ WHERE id = ? AND symbol = ?", session["user_id"], symbol)[0]["share"])
        if shares < sharr:
            return apology("Not enough stock to sell", 400)
        newshare = shares - int(sharr)
        db.execute("UPDATE summ SET share = ? WHERE id = ? AND symbol = ?", newshare, session["user_id"], symbol)
        db.execute("INSERT INTO buy (id, symbol, name, share, price) VALUES(?, ?, ?, ?, ?)",
                   session["user_id"], symbol, name, (-1 * sharr), price)
        oldcash = int(db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"])
        newcash = oldcash + price*sharr
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newcash, session["user_id"])

        return redirect("/")
    return render_template("sell.html", stocks=stocks)

print(os.environ.get("API_KEY"))