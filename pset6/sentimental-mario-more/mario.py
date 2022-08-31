import cs50

# ask user for height of pyramid
height = cs50.get_int("Height: ")
while height < 1 or height > 8:
    height = cs50.get_int("Height: ")

# create pyramids with nested loop
for i in range(height):
    for j in range(height):
        if j < height - 1 - i:
            print(" ", end="")
        else:
            print("#", end="")
    print("  ", end="")
    for j in range(i + 1):
        print("#", end="")
    print()