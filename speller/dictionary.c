// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

#define INDEX LENGTH+1
// Represents a node in a hash table
typedef struct node
{
    char word[INDEX];
    struct node *next;
}
node;

//Choose number of buckets in hash table
const unsigned int N = 24593;

// Hash table
node *table[N];

//creates a global tracker for number of dictionary words
unsigned int sized = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //calculates the index on table of the string using the hash function
    unsigned int hnum = hash(word);

    //transverse the linked list at the index and search for the word
    for (node *tmp = table[hnum]; tmp != NULL; tmp = tmp->next)
    {
        //return true if we find a matching word in the list
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
/*
    The citation below refrences the surce material which contains much of the information that I used as a guideline in creating my hash function

    Sergey, B (1999) Hash table dictionary -- extra credit. http://www.ccs.neu.edu/home/sbratus/com1101/hash-dict.html
    */
unsigned int hash(const char *word)
{
    //initialize variable to store the hash number
    unsigned int h = 0;

    //for each character in a word, convert to lowercase and add the ascii value to hash
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        char c = word[i];


        if (isupper(c))
        {
            c = tolower(c);
        }

        //adds the ascii value to the hash with a seed
        h = (5 * h) + c;
    }

    //returns  the hash value mod the total number of buckets
    return h % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //creates temporalspacefor storing words
    char buffer[INDEX];

    //opens file and checks to make sure file pointer is valid
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    //for every word in the file until the end of the file
    while (fscanf(file, "%s", buffer) != EOF)
    {
        //allocate node space for each new word
        node *string = malloc(sizeof(node));
        if (string == NULL)
        {
            fclose(file);
            return false;
        }

        //copy the word from buffer to the node created above
        strcpy(string->word, buffer);

        //use hash function to determine idx for word
        unsigned int idx = hash(string->word);

        //attach new node to the linked list associated with that index
        string->next = table[idx];
        table[idx] = string;
        sized++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sized;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        node *buffer = table[i];

        while (tmp != NULL)
        {
            buffer = buffer->next;
            free(tmp);
            tmp = buffer;
        }

    }

    return true;
}
