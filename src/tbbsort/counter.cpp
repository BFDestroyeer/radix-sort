#include "tbbsort/counter.h"

namespace TBBSort
{
    Counter::Counter(int* first, int* last, size_t byte_number, size_t* counts) : p_first(first), p_last(last),
        c_byte_number(byte_number), p_counts(counts)
    {

    }

    tbb::task* Counter::execute()
    {
        for (int* i = p_first; i <= p_last; i++)
        {
            p_counts[*((unsigned char*) i + c_byte_number)]++;
        }
        return nullptr;
    }
}