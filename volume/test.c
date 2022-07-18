#include <stdio.h>
#include <stdint.h>

int main(void)
{
    #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

    uint8_t array[44];

    uint8_t size = ARRAY_SIZE(array);

    printf("array size is %i\n", size);
    printf("sizeof(*arr) is %lu\n", sizeof(*array));
    printf("sizeof(arr)[0] is %lu\n", sizeof(array)[0]);
}