#include "tbbsort/relocator.h"

namespace TBBSort
{
    Relocator::Relocator(int* first, int* last, size_t* offsets, size_t byte_number, int* destination)
        : p_first(first), p_last(last), p_offsets(offsets), c_byte_number(byte_number), p_destination(destination)
    {

    }

    tbb::task* Relocator::execute()
    {
        for (int* i = p_first; i <= p_last; i++)
        {
            p_destination[p_offsets[*((unsigned char*) i + c_byte_number)]++] = *i;
        }
        return nullptr;
    }
}