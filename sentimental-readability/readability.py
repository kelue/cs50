from cs50 import get_string
import re


def main():
    # get text from user and store the length of the text
    text = get_string("Text: ")
    length = len(text)
    # printf("%s\n", text)

    # get number of letters in the text
    L = count_letters(text, length)
    # print(f"letters {L}")

    # get number of words in the text
    W = count_words(text)
    # print(f"word {W}")

    # get number of sentences in the text
    S = count_sentences(text, length)
    # print(f"sentences {S}")

    # get index from the formula
    index = get_index(L, W, S)
    # print(f"index {index}")

    # print the grade of the text
    get_grade(index)
    

def count_letters(text, length):
    letterCount = 0

    for i in range(length):
        if text[i].isalpha():
            letterCount += 1

    return letterCount


def count_words(text):
    wordCount = text.count(" ") + 1
    return wordCount


def count_sentences(text, length):
    count = 0

    for i in range(length):
        if re.match('[.?!]', text[i]):
            count += 1

    return count


def get_index(letter, word, sentence):

    # calculate letters per word
    lpw = letter / word * 100

    # calculate sentences per word
    spw = sentence / word * 100

    total = round(0.0588 * lpw - 0.296 * spw - 15.8)

    return total


def get_grade(index):
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()