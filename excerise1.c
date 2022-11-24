#include <stdio.h>

int main()
{
    float f = 1.0;

    // declare pointer  variable
    float *pointer;

    // assign the address of f to pointer

    pointer = &f;

    printf("Value of f = %f\n",  f);
    printf("Address of f = %p\n", &f);
    printf("Value of *pointer = %f\n", *pointer);

    return 0;
}