#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    //for each row
    {
        for (int j = 0; j < width; j++)
        //for each column in the row
        {
            //extract the three channesl from the pixel in row[i] column[j]
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            //caluculate the average of the channel values
            int result = round((red + blue + green)/3.0);

            //asssign the avarage to all values to create a greyscale effect.
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
    for (int i = 0; i < height; i++)
    {
        //for each column in the row
        for (int j = 0; j < width; j++)
        {
            //extract the three channels from the pixel in row[i] column[j]
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            //apply the given formula to obtain respective sepia values for each channel
            float sepiaRed = .393 * red + .769 * green + .189 * blue;
            float sepiaGreen = .349 * red + .686 * green + .168 * blue;
            float sepiaBlue =  .272 * red + .534 * green + .131 * blue;

            //check for any value above the maximum value of 255, if any reset them to 255
            if (sepiaRed >= 255.0)
            {
                sepiaRed = 255.0;
            }
            if (sepiaGreen >= 255.0)
            {
                sepiaGreen = 255.0;
            }
            if (sepiaBlue >= 255.0)
            {
                sepiaBlue = 255.0;
            }

            //assign the sepia values to thier respective channels
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtBlue = round(sepiaBlue);
            image[i][j].rgbtGreen = round(sepiaGreen);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = floor( width / 2.0);
    //for each row
    for (int i = 0; i < height; i++)
    {
        //for each column
        for (int j = 0; j < middle; j++)
        {
            //identify the opposite pixel to be swapped
            int opp = (width - 1) - j;
            //store the opposite pixel in a buffer
            RGBTRIPLE temp = image[i][opp];
            //swap the opposite pixel with the pixel it is to be reversed with
            image[i][opp] = image[i][j];
            //replace the original pixel with its opposite/reverse pixel
            image[i][j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create new array to hold a copy of the image array
    RGBTRIPLE copy[height][width];

    //copy the image array into the temporal copy array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //for each row
    for (int i = 0; i < height; i++)
    {
        //for each column
        for (int j = 0; j < width; j++)
        {
            //initialize row and column variables that will be used to loop across the grid surrounding the pixel
            int rowstart = i - 1;
            int rowend = i + 1;
            int colstart = j - 1;
            int colend = j + 1;

            //check for edge case and adjust the grid row and column values to retain only the part of the grid that we need.
            if (rowstart < 0)
            {
                rowstart = 0;
            }
            if (rowend > height - 1)
            {
                rowend = height - 1;
            }
            if (colstart < 0)
            {
                colstart = 0;
            }
            if (colend > width - 1)
            {
                colend = width - 1;
            }

            int red = 0, blue = 0, green = 0;
            float mean = 0.0;

            // loop through the grid around the pixel and accumulate the values for the channels
            for (int m = rowstart; m <= rowend; m++)
            {
                for (int n = colstart; n <= colend; n++)
                {
                    red += copy[m][n].rgbtRed;
                    blue += copy[m][n].rgbtBlue;
                    green += copy[m][n].rgbtGreen;
                    mean++;
                }
            }

            // calculate the new values for the channels using the total channel value and the average of the grid
            int blurRed = round(red / mean);
            int blurBlue = round(blue / mean);
            int blurGreen = round(green / mean);


            // assign the new values to the original pixel channels
            image[i][j].rgbtRed = blurRed;
            image[i][j].rgbtBlue = blurBlue;
            image[i][j].rgbtGreen = blurGreen;
        }
    }
}
