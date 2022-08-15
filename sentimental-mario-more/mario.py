from cs50 import get_int


def main():
    height = 0

    # prompt user until user enters valid input
    while height < 1 or height > 8:
        height = get_int("Height: ")

    # initialize number of hashes and spaces to be printed on row 1
    no_hash = 1
    no_spaces = height - 1

    for i in range(height):
        spaces(no_spaces)  # print spaces
        hash(no_hash)  # print left hashes

        print("  ", end="")  # print space between left and right hashes
        hash(no_hash)  # print right hashes
        print()  # print new line

        no_spaces -= 1
        no_hash += 1


def spaces(space):
    for i in range(space):
        print(" ", end="")


def hash(hash):
    for i in range(hash):
        print("#", end="")


main()