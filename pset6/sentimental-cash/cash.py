import cs50

# ask user amount of money
dollar = cs50.get_float("Change owed: ")
while dollar <= 0:
    dollar = cs50.get_float("Change owed: ")

# turn its value to cents
dollar = round(dollar * 100)

# calculate amount of quarters
quarters = 0
while dollar >= 25:
    dollar = dollar - 25
    quarters += 1

# calculate amount of dimes
dimes = 0
while dollar >= 10:
    dollar = dollar - 10
    dimes += 1

# calculate amount of nickels
nickels = 0
while dollar >= 5:
    dollar = dollar - 5
    nickels += 1

# calculate amount of pennies
pennies = 0
while dollar >= 1:
    dollar = dollar - 1
    pennies += 1

# print amount of total cents
print(quarters + dimes + nickels + pennies)