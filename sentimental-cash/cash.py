from cs50 import get_float


def main():
    # Ask how many cents the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies
    print(int(coins))


def get_cents():
    while True:
        # prompt the customer for a non negative value
        cents = get_float("Change owed: ")
        if cents >= 0:
            # convert the dollar value to cents
            cents = cents * 100
            break
    return cents


def calculate_quarters(cent):
    return int(cent / 25)


def calculate_dimes(cent):
    return int(cent / 10)


def calculate_nickels(cent):
    return int(cent / 5)


def calculate_pennies(cent):
    return int(cent / 1)


main()