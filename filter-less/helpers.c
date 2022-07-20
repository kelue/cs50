#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, hend = height - 1; i < hend; i++)
    {
        for (int j = 0, wend = width - 1; j < wend; j++)
        {
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            int result = round((red + blue + green)/3.0);

            image[i][j].rgbtRed = result;
            image[i][j].rgbtBlue = result;
            image[i][j].rgbtGreen = result;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //for each row
    for (int i = 0, hend = height - 1; i < hend; i++)
    {
        //for each column in the row
        for (int j = 0, wend = width - 1; j < wend; j++)
        {
            //extract the three channesl from the pixel in row[i] column[j]
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            //apply the given formula ro obtain respective sepia values for each channel
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            int sepiaBlue =  round(.272 * red + .534 * green + .131 * blue);

            //check for any value above the maximum value of 255, if any reset them to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //assign the sepia values to thier respective channels
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
