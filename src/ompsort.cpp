#include "ompsort.h"
#include <iostream>
void ompSort(int* first, int* last, size_t threads_count)
{
    size_t size = last - first + 1;
    size_t* counts = nullptr;
    int* stage_result = new int[size];
    omp_set_num_threads(static_cast<int>(threads_count));
    #pragma omp parallel shared(counts, stage_result)
    {
        int thread_number = omp_get_thread_num();
        int threads_count = omp_get_num_threads();
        size_t part = size / threads_count + 1;
        for (size_t i = 0; i < sizeof(int); i++)
        {
            if (thread_number == 0)
            {
                counts = new size_t[256 * threads_count]();
            }
            //Counting
            #pragma omp barrier
            int* start = first + thread_number * part;
            int* end = first + (thread_number + 1) * part - 1;
            if (end > last)
            {
                end = last;
            }
            for (int* j = start; j <= end; j++)
            {
                counts[*((unsigned char*) j + i) + 256 * thread_number]++;
            }
            //Calculating offset
            #pragma omp barrier
            if (thread_number == 0)
            {
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
            }
            //Relocating
            #pragma omp barrier
            for (int* j = start; j <= end; j++)
            {
                stage_result[counts[*((unsigned char*) j + i) + 256 * thread_number]++] = *j;
            }
            #pragma omp barrier
            if (thread_number == 0)
            {
                std::memcpy(first, stage_result, size * sizeof(int));
                delete[] counts;
            }
        } 
    }
    delete[] stage_result;
}
