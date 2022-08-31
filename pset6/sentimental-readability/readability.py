import re
import cs50

# ask user for text
text = cs50.get_string("Text: ")

# find the number of letters in text
letter = ""
for i in text:
    if i.isalpha():
        letter += i

# find numbers of question marks, dots, exclamation marks and white spaces in the text
qmark = re.findall("\?", text)
dot = re.findall("\.", text)
exclam = re.findall("!", text)
wspace = re.findall(" ", text)

# find the numbers of letters, sentences and words
letters = len(letter)
sentences = len(qmark) + len(dot) + len(exclam)
words = len(wspace) + 1

# calculate Coleman - Liau index for text
L = letters * 100 / words
S = sentences * 100 / words
index = round(0.0588 * L - 0.296 * S - 15.8)

# print grade
if index < 16 and index >= 1:
    print(f"Grade {index}")
elif index >= 16:
    print("Grade 16+")
else:
    print("Before Grade 1")