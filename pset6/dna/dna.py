import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    databases = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            databases.append(row)

    # TODO: Read DNA sequence file into a variable

    with open(sys.argv[2]) as file2:
        for line in file2:
            nucleotids = line
            
    # TODO: Find longest match of each STR in DNA sequence
    new_data = {}
    keys = list(databases[0])
    for key in keys[1:]:
        new_data[key] = longest_match(nucleotids, key)

    # TODO: Check database for matching profiles
    counter = 0
    for data in databases:
        keys1 = list(data)
        keys2 = list(new_data)
        for i in range(len(keys2)):
            if int(data[keys1[1 + i]]) == new_data[keys2[0 + i]]:
                counter += 1
            if counter == len(keys2):
                print(data["name"])
                sys.exit(0)
        counter = 0
    print("No match")

    return


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
