#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


bool validateKey(int args, string key);

int main(int argc, string argv[])
{
    //check for result of validate key and if it is false it terminates the program
    if (!validateKey(argc, argv[1]))
    {
        return 1;
    }

    char key[26];
    //An array to store the values of the key

    for (int i = 0; i < 26; i++)
    {
        key[i] = argv[1][i];
        //maps each value to an array index
        //printf("Array index %i is %c\n", i, key[i]);
    }

    string text = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, len = strlen(text); i < len; i++)
        //this loop  is where each value in the string is encrypted
    {
        if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
        else if (isupper(text[i]))
        {
            printf("%c", toupper(key[text[i] - 65]));
        }
        else
        {
            printf("%c", tolower(key[text[i] - 97]));
        }
    }
    printf("\n");

    return 0;
}

bool validateKey(int args, string key)
{
    if (args < 2 || args > 2)
    {
        printf("Usage: ./substitution key\n");
        return false;
    }
    else if (strlen(key) < 26 || strlen(key) > 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("All values of key must be alphabets\n");
            return false;
        }
    }

    //this loop checks duplicate values by incrementing a check variable for the number of times a particular value is duplicated. i.e when the i loop matches j loop. They are expected to match only once, so if check > 0 then theres a duplicate and the key is invalid
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        int check = 0;
        for (int j = 0; j < len; j++)
        {
            if (key[i] == key[j])
            {
                check++;
            }
        }

        if (check > 1)
        {
            printf("key should not contain duplicate values\n");
            return false;
        }
    }
    return true;
}