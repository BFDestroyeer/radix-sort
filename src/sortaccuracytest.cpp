#include "sortaccuracytest.h"

bool sorted(int *begin, int *end)
{
    for (int* i = begin; i < end; i++)
    {
        if (*i > *(i + 1))
        {
            return false;
        }
    }
    return true;
}

void sortAccuracyTest(size_t size)
{
    

    //MPI sort
    int rank, process_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    if (rank == 0)
    {
        int *array = new int[size];
        fillWhitRandom(array, size);
        MPI_Barrier(MPI_COMM_WORLD);
        mpiSort(array, array + size - 1);
        if (sorted(array, array + size - 1))
        {
            std::cout << "[RIGHT] MPI sort" << std::endl;
        }
        else
        {
            std::cout << "[WRONG] MPI sort" << std::endl;
            for (size_t i = 0; i < size; i++)
            {
                std::cout << array[i] << ' ';
            }
        }
    }
    else
    {
        MPI_Barrier(MPI_COMM_WORLD);
        mpiSort(nullptr, nullptr);
        return;
    }

    int *array = new int[size];

    //Recursive seqential sort
    fillWhitRandom(array, size);
    recursiveSequentialSort(array, array + size - 1);
    if (sorted(array, array + size - 1))
    {
        std::cout << "[RIGHT] Recursive sequential sort" << std::endl;
    }
    else
    {
        std::cout << "[WRONG] Recursive sequential sort" << std::endl;
    }

    //Sequential sort
    fillWhitRandom(array, size);
    sequentialSort(array, array + size - 1);
    if (sorted(array, array + size - 1))
    {
        std::cout << "[RIGHT] Sequential sort" << std::endl;
    }
    else
    {
        std::cout << "[WRONG] Sequential sort" << std::endl;
    }

    //Thread sort
    fillWhitRandom(array, size);
    threadSort(array, array + size - 1);
    if (sorted(array, array + size - 1))
    {
        std::cout << "[RIGHT] Thread sort" << std::endl;
    }
    else
    {
        std::cout << "[WRONG] Thread sort" << std::endl;
    }

    //OpenMP sort
    fillWhitRandom(array, size);
    ompSort(array, array + size - 1);
    if (sorted(array, array + size - 1))
    {
        std::cout << "[RIGHT] OpenMP sort" << std::endl;
    }
    else
    {
        std::cout << "[WRONG] OpenMP sort" << std::endl;
    }

    //Intel TBB sort
    fillWhitRandom(array, size);
    tbbSort(array, array + size - 1, 3);
    if (sorted(array, array + size - 1))
    {
        std::cout << "[RIGHT] Intel TBB sort" << std::endl;
    }
    else
    {
        std::cout << "[WRONG] Intel TBB sort" << std::endl;
    }
}
