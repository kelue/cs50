//this file was usedfor testing different ideas before implementing in main code

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define INDEX 47+1

unsigned int check = 0;

unsigned int hash(const char *word);
unsigned int checked(void);
void lower(const char *word);

int main(void)
{
    // float a = 0.5 *(sqrt(5)-1);
    // printf("a is %f :\n", a);
    // float s = 222 * a;
    // printf("s is %f :\n", s);

    // float x = s - (int)s;
    // printf("x is %f :\n", x);


//code for loading dictionary
    // char buffer[INDEX];


    // FILE *file = fopen("./dictionaries/small", "r");

    // while(fscanf(file, "%s", buffer) != EOF)
    // {
    //     char word[INDEX];
    //     strcpy(word, buffer);
    //     printf("%s\n", word);
    // }

    // fclose(file);

    char *A = "atlanti";
    char B[10] = "Atlanti's";
    char C[9] = "atlANTIS";

    // unsigned int AA = hash(A);
    // printf("hash of A is: %i\n", AA);

    // unsigned int BB = hash(B);
    // printf("hash of B is: %i\n",BB);

    // unsigned int CC = hash(C);
    // printf("hash of C is: %i\n", CC);

    // unsigned int dicA = hash("atlanti");
    // printf("hash of dicA is: %i\n", dicA);

    // unsigned int dicB = hash("atlanti's");
    // printf("hash of dicB is: %i\n", dicB);

    // unsigned int dicC = hash("atlantis");
    // printf("hash of dicC is: %i\n", dicC);

    //printf("number of words checked is %s\n", lower(B));

    lower(B);
    lower(C);
}

void lower(const char *word)
{
    int len = strlen(word) + 1;
    printf("length of word is %i\n", len);

    char string[len];

    for (int i = 0; i < len; i++)
    {
        // if (isupper(word[i]))
        // {
        //     //char tmp = word[i] + 32;
        //     string[i] = (char)tolower(word[i]);
        // }
        // else
        // {
        //     string[i] = word[i];
        // }
        string[i] = (char)tolower(word[i]);
    }

    printf("string is %s\n", string);

}

unsigned int hash(const char *word)
{
    unsigned int h = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        char c = word[i];
        //h = 5 *h + word[i]

        if (isupper(c))
        {
            c = tolower(c);
        }

        h = (5 * h) + c;
    }

    check++;
    return h % 26;
}

unsigned int checked(void)
{
    return check;
}
