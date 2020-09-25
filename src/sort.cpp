#include "sort.h"


void linearSort(int* first, int* last)
{
    int min = *std::min_element(first, last);
    linearSortStage(first, last, sizeof(int) * 8);
    if (min < 0)
    {
        relocateNegatives(first, last);
    }
}

void linearSortStage(int* first, int* last, size_t order)
{
    if ((order == 0) || (last <= first))
    {
        return;
    }

    size_t mask = ((size_t) 1) << (order - 1);
    int *begin = first, *end = last;
    while (begin <= end)
    {
        if ((*begin & mask) && !(*end & mask))
        {
            int temp = *begin;
            *begin = *end;
            *end = temp;
            begin++;
            end--;
        }
        else
        {
            if(!(*begin & mask))
            {
                begin++;
            }
            if (*end & mask)
            {
                end--;
            }
        }
    }
    linearSortStage(first, end, order - 1);
    linearSortStage(begin, last, order - 1);
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