#include "functions.h"

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