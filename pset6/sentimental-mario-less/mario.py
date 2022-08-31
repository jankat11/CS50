import cs50

# ask user for height of the pyramid
height = cs50.get_int("Height: ")
while height < 1 or height > 8:
    height = cs50.get_int("Height: ")


# make nested loop to draw pyramid with given height
for i in range(height):
    for j in range(height):
        if j < height - i - 1:
            print(" ", end="")
        else:
            print("#", end="")
    print()

