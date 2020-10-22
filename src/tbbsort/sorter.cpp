#include "tbbsort/sorter.h"

namespace TBBSort
{
    Sorter::Sorter(int* first, int* last, size_t threads_count) : p_first(first),
        p_last(last), c_threads_count(threads_count)
    {

    }

    tbb::task* Sorter::execute()
    {
        int* stage_result = new int[p_last - p_first + 1];
        size_t part = (p_last - p_first + 1) / c_threads_count;
        Counter** counters = new Counter*[c_threads_count];
        Relocator** relocators = new Relocator*[c_threads_count];
        for (size_t i = 0; i < sizeof(int); i++)
        {
            //Counting
            size_t* counts = new size_t[256 * c_threads_count]();
            for (size_t j = 0; j < c_threads_count - 1; j++)
            {
                counters[j] = new (allocate_child())
                    Counter(p_first + j * (part + 1), p_first + j * (part + 1) + part, i, counts + 256 * j);
            }
            counters[c_threads_count - 1] = new (allocate_child())
                Counter(p_first + (c_threads_count - 1) * (part + 1), p_last, i, counts + 256 * (c_threads_count - 1));
            set_ref_count(static_cast<int>(c_threads_count) + 1);
            for (size_t j = 0; j < c_threads_count; j++)
            {
                spawn(*(counters[j]));
            }
            wait_for_all();
            //Calculating offset (at counts array)
            size_t sum = 0;
            for (size_t j = 0; j < 256; j++)
            {
                for (size_t k = 0; k < c_threads_count; k++)
                {
                    size_t temp = counts[j + k * 256];
                    counts[j + k * 256] = sum;
                    sum += temp;
                }
            }
            //Relocating
            for (size_t j = 0; j < c_threads_count - 1; j++)
            {
                relocators[j] = new (allocate_child()) Relocator(p_first + j * (part + 1),
                    p_first + j * (part + 1) + part, counts + 256 * j, i, stage_result);
            }
            relocators[c_threads_count - 1] = new (allocate_child())
                Relocator(p_first + (c_threads_count - 1) * (part + 1), p_last, counts + 256 * (c_threads_count - 1),
                    i, stage_result);
            set_ref_count(static_cast<int>(c_threads_count) + 1);
            for (size_t j = 0; j < c_threads_count; j++)
            {
                spawn(*(relocators[j]));
            }
            wait_for_all();
            std::memcpy(p_first, stage_result, (p_last - p_first + 1) * sizeof(int));
            delete[] counts;
        }
        delete[] stage_result;
        delete[] counters;
        delete[] relocators;
        return nullptr;
    }
}

