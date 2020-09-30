#include <time.h>

#include <chrono>
#include <iostream>
#include <random>

#include "recursivesequentialsort.h"
#include "sequentialsort.h"

int main(int argc, char* argv[])
{
    size_t size = 1000000;
    int* array = new int[size];

    srand((unsigned) time(0));
    for(size_t i = 0; i < size; i++)
    {
        array[i] = rand();
    }

    auto sequential_begin = std::chrono::steady_clock::now();
    sequentialSort(array, array + size - 1);
    auto sequential_end = std::chrono::steady_clock::now();
    std::cout << "Sequential: " << std::chrono::duration_cast<std::chrono::milliseconds>(sequential_end - sequential_begin).count() << "ms"<< std::endl;

    srand((unsigned) time(0));
    for(size_t i = 0; i < size; i++)
    {
        array[i] = rand();
    }

    auto recursive_sequential_begin = std::chrono::steady_clock::now();
    recursiveSequentialSort(array, array + size - 1);
    auto recursive_sequential_end = std::chrono::steady_clock::now();
    std::cout << "Recursive sequential: " << std::chrono::duration_cast<std::chrono::milliseconds>
        (recursive_sequential_end - recursive_sequential_begin).count() << "ms"<< std::endl;

    /*for (size_t i = 0; i < size; i++)
    {
        std::cout << array[i] << ' ';
    }*/

    

    return 0;
}