#include "threadsort.h"

void threadSort(int* first, int* last, size_t threads_count)
{
    std::thread** threads = new std::thread*[threads_count];
    size_t part = (last - first + 1) / threads_count;
    size_t* counts = new size_t[256 * threads_count];
    for (size_t i = 0; i < sizeof(int); i++)
    {
        //Counting
        memset(counts, 0, 256 * threads_count * sizeof(size_t));
        for (size_t j = 0; j < threads_count - 1; j++)
        {
            threads[j] = new std::thread(counter, first + j * (part + 1), first + j * (part + 1) + part, i, counts + 256 * j);
        }
        threads[threads_count - 1] = new std::thread(counter, first + (threads_count - 1) * (part + 1), last, i, counts + 256 * (threads_count - 1));
        for (size_t j = 0; j < threads_count; j++)
        {
            threads[j]->join();
            delete threads[j];
        }
        //Calculating offset (at counts array)
        size_t summ = 0;
        for (size_t j = 0; j < 256; j++)
        {
            for (size_t k = 0; k < threads_count; k++)
            {
                size_t temp = counts[j + k * 256];
                counts[j + k * 256] = summ;
                summ += temp;
            }
        }
        //Relocating
        int* stage_result = new int[last - first + 1];
        for (size_t j = 0; j < threads_count - 1; j++)
        {
            threads[j] = new std::thread(relocator, first + j * (part + 1), first + j * (part + 1) + part, counts + 256 * j, i, stage_result);
        }
        threads[threads_count - 1] = new std::thread(relocator, first + (threads_count - 1) * (part + 1), last, counts + 256 * (threads_count - 1), i, stage_result);
        for (size_t j = 0; j < threads_count; j++)
        {
            threads[j]->join();
            delete threads[j];
        }
        memcpy(first, stage_result, (last - first + 1) * sizeof(int));
        delete[] stage_result;
    }
    delete[] threads;
    delete[] counts;
}

void counter(int* first, int* last, size_t byte_number, size_t* counts)
{
    for (int* i = first; i <= last; i++)
    {
            counts[*((unsigned char*) i + byte_number)]++;
    }
}

void relocator(int* first, int* last, size_t* offsets, size_t byte_number, int* destination)
{
    for (int* i = first; i <= last; i++)
    {
        destination[offsets[*((unsigned char*) i + byte_number)]++] = *i;
    }
}