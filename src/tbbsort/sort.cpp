#include "tbbsort/sort.h"

namespace TBBSort
{
    Sort::Sort(int* first, int* last, size_t threads_count) : p_first(first),
        p_last(last), c_threads_count(threads_count)
    {

    }

    tbb::task* Sort::execute()
    {
        Counter** counters = new Counter*[c_threads_count];
        Relocator** relocators = new Relocator*[c_threads_count];
        size_t part = (p_last - p_first + 1) / c_threads_count;
        for (size_t i = 0; i < sizeof(int); i++)
        {
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
                spawn(*(counters[i]));
            }
            wait_for_all();
        }
        return nullptr;
    }
}