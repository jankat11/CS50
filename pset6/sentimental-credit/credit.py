import cs50

# get credit number from user
card_no = cs50.get_string("Number: ")

digit_len = len(card_no)

# check if the number is valid according luhn's algorithm


def Luhn_legit():
    toplam = 0
    for i in range(1, digit_len, 2):
        mult = 2 * int(card_no[digit_len - 1 - i])
        if len(str(mult)) == 2:
            mult = str(mult)
            mult = int(mult[0]) + int(mult[1])
            mult = int(mult)
        toplam = toplam + mult
    for i in range(0, digit_len, 2):
        toplam = toplam + int(card_no[digit_len - 1 - i])
    if toplam % 10 == 0:
        return True
    else:
        return False


# if luhn not correct print invalid
if Luhn_legit() == False:
    print("INVALID")
# check according card
if (card_no[0] + card_no[1] == "37" or card_no[0] + card_no[1] == "34") and len(card_no) == 15:
    print("AMEX")
elif (int(card_no[0] + card_no[1]) >= 51 and int(card_no[0] + card_no[1]) <= 55) and len(card_no) == 16:
    print("MASTERCARD")
elif card_no[0] == "4" and (len(card_no) == 13 or len(card_no) == 16):
    print("VISA")