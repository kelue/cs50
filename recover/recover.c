#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

//alias for 8bit
typedef uint8_t BYTE;

//number of bytes in a block
const int BLOCK_SIZE = 512;

//defines a consr that calculates the size of an array
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


//function prototypes
bool checkHeader(BYTE array[]);

int main(int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover inputfile \n");
        return 1;
    }

    //get the name of the input file and store it in a string
    char *infile = argv[1];

    //open the input file, if the input file does not exist,terminate the program
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("could not open %s.\n", infile);
        fclose(inptr);
        return 1;
    }

    //create a buffer to temporarily store 512B blocks
    BYTE buffer[BLOCK_SIZE];

    //initialize variable to keep track of number of jpeg images
    int jpgFile = -1 ;

    //allocate memory for jpeg filenames
    char *filename = malloc(sizeof(char) * 8);

    // //initialise location for storing the current image
    FILE *img;

    //while the end of the file has not been reached
    while (fread(buffer, ARRAY_SIZE(buffer), 1, inptr) == 1)
    {
        //function checks if the block contains header for a jpeg file
        //returns tue it does else false
        bool check = checkHeader(buffer);

        //if the block in the buffer is a header block
        if (check)
        {
            //check to see if an img file is already open
            if (jpgFile == -1)
            {
                //initialise filename
                jpgFile = 0;

                //create new image file name
                sprintf(filename, "%03i.jpg", jpgFile);

                //open new image file using new filename
                img = fopen(filename, "w");

                //write block in buffer to image file
                fwrite(buffer, ARRAY_SIZE(buffer), 1, img);
            }
            else
            {
                //close the image previous image file
                fclose(img);

                //increment current image
                jpgFile++;

                //create new image file name
                sprintf(filename, "%03i.jpg", jpgFile);

                //open new image file using new filename
                img = fopen(filename, "w");

                if (img == NULL)
                {
                    printf("Unable to open image. \n");
                    free(filename);
                    fclose(inptr);
                    return 1;
                }

                //write block in buffer to image file
                fwrite(buffer, ARRAY_SIZE(buffer), 1, img);
            }
        }
        else
        {
            if (jpgFile != -1)
            {
                fwrite(buffer, ARRAY_SIZE(buffer), 1, img);
            }
        }
    }

    //free all memory and close all open files
    fclose(img);
    free(filename);
    fclose(inptr);
}

/*
this checkHeader function checks to see if the block is a jpeg header.
It returns false if any of the header bytes does not match the specification,
and true if it does.
*/
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