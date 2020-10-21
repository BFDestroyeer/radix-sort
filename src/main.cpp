#include <array>
#include <chrono>
#include <string>
#include <iostream>
#include <thread>

#include <mpi.h>

#include "tbb/task_scheduler_init.h"

#include "functions.h"
#include "logger.h"
#include "mpisort.h"
#include "ompsort.h"
#include "recursivesequentialsort.h"
#include "sequentialsort.h"
#include "tbbsort.h"
#include "threadsort.h"

int main(int argc, char* argv[])
{
    tbb::task_scheduler_init init(std::thread::hardware_concurrency());
    MPI_Init(&argc, &argv);
    int rank, process_count, thread_count = 1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    if (argc < 2)
    {
        std::cout << "Wrong nuber of arguments" << std::endl;
    }
    std::string argument(argv[1]);
    std::string sort_name;
    std::array<std::chrono::milliseconds, 3> results;
    size_t size = 10000000;
    int* array = nullptr;
    for (size_t i = 0; i < 3; i++)
    {
        array = new int[size];
        if (rank == 0)
        {
            fillWhitRandom(array, size);
        }
        if (argument == "-rseq") //Recursive sequential sort
        {
            sort_name = "Recursive sequential sort";
            auto begin_time = std::chrono::steady_clock::now();
            recursiveSequentialSort(array, array + size - 1);
            auto end_time = std::chrono::steady_clock::now();
            results[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
        }
        else if (argument == "-seq") //Sequential sort
        {
            sort_name = "Sequential sort";
            auto begin_time = std::chrono::steady_clock::now();
            sequentialSort(array, array + size - 1);
            auto end_time = std::chrono::steady_clock::now();
            results[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
        }
        else if (argument == "-thread") //Thread sort
        {
            sort_name = "Thread sort";
            thread_count = std::thread::hardware_concurrency();
            auto begin_time = std::chrono::steady_clock::now();
            threadSort(array, array + size - 1);
            auto end_time = std::chrono::steady_clock::now();
            results[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
        }
        else if (argument == "-mpi") //MPI sort
        {
            sort_name = "MPI Internal sort";
            thread_count = process_count;
            if (rank == 0)
            {
                MPI_Barrier(MPI_COMM_WORLD);
                auto begin_time = std::chrono::steady_clock::now();
                mpiSort(array, array + size - 1);
                auto end_time = std::chrono::steady_clock::now();
                results[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
            }
            else
            {
                MPI_Barrier(MPI_COMM_WORLD);
                mpiSort(nullptr, nullptr);
                }
        }
        else if (argument == "-omp") //OpenMP sort
        {
            sort_name = "OpenMP sort";
            thread_count = std::thread::hardware_concurrency();
            auto begin_time = std::chrono::steady_clock::now();
            ompSort(array, array + size - 1);
            auto end_time = std::chrono::steady_clock::now();
            results[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
        }
        else if (argument == "-tbb") //Intel TBB sort
        {
            sort_name = "TBB sort";
            thread_count = std::thread::hardware_concurrency();
            auto begin_time = std::chrono::steady_clock::now();
            tbbSort(array, array + size - 1, thread_count);
            auto end_time = std::chrono::steady_clock::now();
            results[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
        }
        delete[] array;
        size *= 10;
    }
    MPI_Finalize();
    if (rank != 0)
    {
        return 0;
    }
    std::cout << '|' << sort_name << '|' << thread_count << '|' << results[0].count() << '|' << results[1].count() << '|' << results[2].count() << '|' << std::endl;
    return 0;
}
