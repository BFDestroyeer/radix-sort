#include <chrono>

#include "functions.h"
#include "logger.h"
#include "recursivesequentialsort.h"
#include "sequentialsort.h"
#include "threadsort.h"

int main(int argc, char* argv[])
{
    Logger logger;
    size_t size = 10000000;
    long long results[3][3];

    for (size_t i = 0; i < 3; i++)
    {
        int* array = new int[size];

        fillWhitRandom(array, size);
        auto recursive_sequential_begin = std::chrono::steady_clock::now();
        recursiveSequentialSort(array, array + size - 1);
        auto recursive_sequential_end = std::chrono::steady_clock::now();
        results[0][i] = std::chrono::duration_cast<std::chrono::milliseconds>(recursive_sequential_end - recursive_sequential_begin).count();

        fillWhitRandom(array, size);
        auto sequential_begin = std::chrono::steady_clock::now();
        sequentialSort(array, array + size - 1);
        auto sequential_end = std::chrono::steady_clock::now();
        results[1][i] = std::chrono::duration_cast<std::chrono::milliseconds>(sequential_end - sequential_begin).count();
        
        fillWhitRandom(array, size);
        auto thread_begin = std::chrono::steady_clock::now();
        threadSort(array, array + size - 1);
        auto thread_end = std::chrono::steady_clock::now();
        results[2][i] = std::chrono::duration_cast<std::chrono::milliseconds>(thread_end - thread_begin).count();

        size *= 10;
        delete[] array;
    }
 
    logger.log("Recursive sequential sort", results[0][0], results[0][1], results[0][2]);
    logger.log("Sequential sort", results[1][0], results[1][1], results[1][2]);
    logger.log("Thread sort", results[2][0], results[2][1], results[2][2]);



    return 0;
}