#include <chrono>
#include <iostream>
#include <thread>

#include "functions.h"
#include "logger.h"
#include "recursivesequentialsort.h"
#include "sequentialsort.h"
#include "threadsort.h"

int main(int argc, char* argv[])
{
    size_t size = 10000000;
    std::chrono::nanoseconds results[3][3];

    /*for (size_t i = 0; i < 3; i++)
    {
        int* array = new int[size];

        fillWhitRandom(array, size);
        auto recursive_sequential_begin = std::chrono::steady_clock::now();
        recursiveSequentialSort(array, array + size - 1);
        auto recursive_sequential_end = std::chrono::steady_clock::now();
        results[0][i] = recursive_sequential_end - recursive_sequential_begin;

        fillWhitRandom(array, size);
        auto sequential_begin = std::chrono::steady_clock::now();
        sequentialSort(array, array + size - 1);
        auto sequential_end = std::chrono::steady_clock::now();
        results[1][i] = sequential_end - sequential_begin;
        
        fillWhitRandom(array, size);
        auto thread_begin = std::chrono::steady_clock::now();
        threadSort(array, array + size - 1);
        auto thread_end = std::chrono::steady_clock::now();
        results[2][i] = thread_end - thread_begin;

        size *= 10;
        delete[] array;
    }*/
 
    Logger::instance().log("Recursive sequential sort", 1, results[0][0], results[0][1], results[0][2]);
    Logger::instance().log("Sequential sort", 1, results[1][0], results[1][1], results[1][2]);
    Logger::instance().log("Thread sort", std::thread::hardware_concurrency(), results[2][0], results[2][1], results[2][2]);

    std::cout << "Done" << std::endl;

    return 0;
}
