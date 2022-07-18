// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //this creates an array with the header size that we will use to hold the bytes we read from the wav header
    uint8_t header[HEADER_SIZE];

    /*
    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

    This function writes data to a file that has been opened via fopen. It expects as input:
    ptr, which is the address (of the first byte) of memory from which to read the data,
    size, which is the size (in bytes) of the type of data to write,
    nmemb, which is the number of those types to write at once, and
    stream, which is the pointer to a FILE returned by fopen.

    Below the size of the item is 44bytes(header_size), and only 1 is needed which is the size of the header(I think this is a coincidence and maybe I should just have used 1 but whatever it works)
    */


    fread(header, HEADER_SIZE, sizeof(*header), input);
    fwrite(header, HEADER_SIZE, sizeof(*header), output);

    //printf("size of header %lu\n", sizeof(header));

    int16_t buffer;


    while(1)
    {
        //read the data from the file and save to buffer
        size_t ret = fread(&buffer, sizeof(int16_t), 1, input);

        //check to see if no data is read
        if (ret == 0)
        {
            break;
        }

        //update the sample by multiplying by factor
        buffer *= factor;

        //write the sample to the file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
