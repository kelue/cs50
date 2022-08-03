#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

//testing array size and block allocation for fread

//alias for 8bit
typedef uint8_t BYTE;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


//number of bytes in a block
const int BLOCK_SIZE = 514;

//function prototypes
bool checkHeader(BYTE array[]);

int main(void)
{
    BYTE buffer[BLOCK_SIZE];


    buffer[0] = 0xaf;
    buffer[1] = 0xd8;
    buffer[2] = 0xff;
    buffer[3] = 0xe9;

    int size = ARRAY_SIZE(buffer);
    printf("buffer size is %i\n", size);
    printf("element size is %lu\n", sizeof(buffer[0]));


    bool check = checkHeader(buffer);

    if (check)
    {
        printf("is JPEG header\n");
    }
    else
    {
        printf("not a JPEG header\n");
    }

}

bool checkHeader(BYTE array[])
{
    if (array[0] != 0xff)
    {
        return false;
    }
    if (array[1] != 0xd8)
    {
        return false;
    }
    if (array[2] != 0xff)
    {
        return false;
    }
    if ((array[3] & 0xf0) != 0xe0)
    {
        return false;
    }

    return true;
}