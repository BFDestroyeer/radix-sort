#include <iostream>

#include "sort.h"

int main(int argc, char* argv[])
{
    int array[] = {10, 53, 31, 54, 18, 42, 14, 56, 28};
    linearSort(array, array + 8);

    for (size_t i = 0; i < 8; i++)
    {
        std::cout << array[i] << ' ';
    }

    return 0;
}