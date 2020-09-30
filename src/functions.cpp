#include "functions.h"

void fullWhitRandom(int* array, size_t size)
{
    srand((unsigned) time(0));
    for(size_t i = 0; i < size; i++)
    {
        array[i] = rand();
    }
}

void relocateNegatives(int* first, int* last)
{
    size_t size = last - first + 1;
    int* result = new int[size];
    int* separator = first;
    for (; (separator <= last) && !(*separator < 0); separator++)
    {

    }
    size_t i = 0;
    for (int* j = separator; j <= last; j++, i++)
    {
        result[i] = *j;
    }
    for (int* j = first; j < separator; j++, i++)
    {
        result[i] = *j;
    }
    for (size_t k = 0; k < size; k++)
    {
        first[k] = result[k];
    }
}