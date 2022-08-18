from csv import DictReader
from sys import argv


def main():
    # check for proper usage
    if len(argv) != 3:
        print("Incorrect arguments, Program requires two arguments")
        exit(1)

    # intialize lists for storing database and STRs
    people = []
    fields = []

    # open database file
    with open(argv[1], "r") as file:
        reader = DictReader(file)

        # from each row create a dict of person and add to the list
        for person in reader:
            people.append(person)

        # store the column headers to fields list, we will extract the STR subsequences to check here
        for field in reader.fieldnames:
            fields.append(field)

    # remove the name column leaving only the desired STR headers
    fields = fields[1:]

    #  open the sequence file and read it
    with open(argv[2], "r") as f:
        dna = f.read()

    # dictionary for storing longest sequence for each respective STR
    genome = {}

    # for each STR in the fields list find the value of longest match and store in the genome dict with STR as key
    for strand in fields:
        count = longest_match(dna, strand)
        genome[strand] = count

    # store the number of strands
    match = len(fields)

    # for each person check if their STR counts match, if it does update the count variable
    for person in people:
        count = 0
        for strand in fields:
            if int(person[strand]) == genome[strand]:
                count += 1
        # if all the STRs match then the DNAs must be from the same person
        if count == match:
            print(person["name"])
            exit(1)

    # if none of the persons match the dna then default to this and exit the program
    print("No match")
    exit(1)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
