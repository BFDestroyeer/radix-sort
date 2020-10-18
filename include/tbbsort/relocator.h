#pragma once

#include "tbb/task.h"

namespace TBBSort
{
    class Relocator : public tbb::task
    {
        protected:
        int* p_first;
        int* p_last;
        size_t* p_offsets;
        const size_t c_byte_number;
        int* p_destination;

        public:
        Relocator(int* first, int* last, size_t* offsets, size_t byte_number, int* destination);
        ~Relocator() = default;

        tbb::task* execute();
    };
}