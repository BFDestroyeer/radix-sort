#include <time.h>

#include <iostream>
#include <random>

#include "sort.h"

int main(int argc, char* argv[])
{
    size_t size;
    std::cout << "Please, input array size: ";
    std::cin >> size;
    int* array = new int[size];

    srand((unsigned) time(0));
    for(size_t i = 0; i < size; i++)
    {
        array[i] = rand() % 10000 - 5000;
    }

    linearSort(array, array + size - 1);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << array[i] << ' ';
    }

    return 0;
}