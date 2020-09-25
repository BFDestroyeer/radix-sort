#include "sort.h"


void linearSort(int* first, int* last)
{
    linearSortStage(first, last, 8);
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