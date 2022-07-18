#include <cs50.h>
#include <stdio.h>

void hash(int hash);
void space(int space);


int main(void)
{

    int height;

    do
    {
        height = get_int("Height: ");//prompt user for valid input
    }
    while (height < 1 || height > 8);

    int no_spaces = height - 1;
    int no_hash = 1;

    for (int i = 0; i < height; i++)//for each row
    {
        space(no_spaces);//print space
        hash(no_hash);//print left aligned hashes

        printf("  ");
        hash(no_hash); //print right aligned hashes
        printf("\n");

        no_spaces--; //decrement number of spaces
        no_hash++; //incrememnt number of hashes
    }
}

void hash(int hash)
{
    int i = 0;
    while (i < hash)
    {
        printf("#");
        i++;
    }
}

void space(int space)
{
    int i = 0;
    while (i < space)
    {
        printf(" ");
        i++;
    }
}