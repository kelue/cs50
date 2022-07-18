#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int get_index(int letter, int word, int sentence);
void get_grade(int index);
//index = 0.0588 * L - 0.296 * S - 15.8
// L / words * 100 = letters per 100 words
// S / words * 100 = sentences per 100 words
int main(void)
{
    string text = get_string("Text: ");
    //printf("%s\n", text);

    int L = count_letters(text);
    //printf("%i letters\n", L);

    int W = count_words(text);
    //printf("%i words\n", W);

    int S = count_sentences(text);
    //printf("%i sentences\n", S);

    int index = get_index(L, W, S);
    //printf("%i index\n", index);

    get_grade(index);
}

int count_letters(string text)//calculates number of letters in the text
{
    int letterCount = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
            letterCount++;
    }

    return letterCount;
}

int count_words(string text)//calculates number of words in the text
{
    int wordCount = 1;
    int length = strlen(text);

    for(int i = 0; i <= length; i++)
    {
        if((int) text[i] == 32)
            wordCount++;
    }

    return wordCount;
}

int count_sentences(string text)//calculates number of sentences in the text
{
    int sentenceCount = 0;
    int length = strlen(text);

    for(int i = 0; i <= length; i++)
    {
        if((int) text[i] == 33 || (int) text[i] == 46 || (int) text[i] == 63)
            sentenceCount++;
    }

    return sentenceCount;
}

int get_index(int letter, int word, int sentence)
{
    float lpw = letter / (float) word * 100;
    //where LPW is letters per 100 words
    float spw = sentence / (float) word * 100;
    //where SPW is letters per 100 words

    return round(0.0588 * lpw - 0.296 * spw - 15.8); //Coleman-Liau index caluculator.
}

void get_grade(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }else{
        printf("Grade %i\n", index);
    }
}