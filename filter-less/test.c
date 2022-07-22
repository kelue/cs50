#include <stdio.h>
#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <math.h>

long random(void);

int main(void)
{
    int mean = 0;
    int red = 0;

int num = (random() / ((double) RAND_MAX + 1)) * 255;

for(int i = 0; i < num; i++)
{
    red++;
}
printf("red %i\n", red);

int number = (random() / ((double) RAND_MAX + 1)) * 9;

for(int i = 0; i < number; i++)
{
    mean++;
}
printf("mean %i\n", mean);


float result = red / mean;
printf("result %f\n", result);

int res = round(red / mean);
printf("result %d\n", res);
}