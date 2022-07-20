#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int cal(RGBTRIPLE image);

    for (int i = 0, end = height -1; i < end; i++)
    {
        for (int j = 0, end = width -1; j < end; j++)
        {
            cal(image[i][j]);
        }
    }

    int cal(RGBTRIPLE image)
    {
        int red = image.rgbtRed;
        int blue = image.rgbtBlue;
        int green = image.rgbtGreen;

        int result = round((red + blue + green))
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
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
