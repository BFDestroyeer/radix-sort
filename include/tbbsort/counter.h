#pragma once

#include "tbb/task.h"

namespace TBBSort
{
    class Counter : public tbb::task
    {
        protected:
        int* p_first;
        int* p_last;
        const size_t c_byte_number;
        size_t* p_counts;

        public:
        Counter(int* first, int* last, size_t byte_number, size_t* counts);
        ~Counter() = default;

        tbb::task* execute();
    };
}
