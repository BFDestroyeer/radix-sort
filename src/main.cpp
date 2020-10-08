#include <chrono>
#include <iostream>
#include <thread>

#include <mpi.h>

#include "functions.h"
#include "logger.h"
#include "mpisort.h"
#include "recursivesequentialsort.h"
#include "sequentialsort.h"
#include "threadsort.h"

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int rank, process_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    size_t size = 10000000;
    std::chrono::nanoseconds results[4][3] = {};

    for (size_t i = 0; i < 2; i++)
    {
        if (rank == 0)
        {
            int* array = new int[size];
            fillWhitRandom(array, size);
            MPI_Barrier(MPI_COMM_WORLD);
            auto mpi_begin = std::chrono::steady_clock::now();
            mpiSort(array, array + size - 1, rank);
            auto mpi_end = std::chrono::steady_clock::now();
            results[3][i] = mpi_end - mpi_begin;

            size *= 10;
            delete[] array;
        }
        else
        {
            MPI_Barrier(MPI_COMM_WORLD);
            mpiSort(nullptr, nullptr, rank);
        }
    }
    if (rank == 0)
    {
        size = 10000000;
    }
    else
    {
        MPI_Finalize();
        return 0;
    }
    
    for (size_t i = 0; i < 3; i++)
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
    }
 
    Logger::instance().log("Recursive sequential sort", 1, results[0][0], results[0][1], results[0][2]);
    Logger::instance().log("Sequential sort", 1, results[1][0], results[1][1], results[1][2]);
    Logger::instance().log("Thread sort", std::thread::hardware_concurrency(), results[2][0], results[2][1], results[2][2]);
    Logger::instance().log("MPI Internal sort", process_count, results[3][0], results[3][1], results[3][2]);

    std::cout << "Done" << std::endl;

    MPI_Finalize();
    return 0;
}
