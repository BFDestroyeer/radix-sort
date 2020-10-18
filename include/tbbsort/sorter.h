#pragma once

#include <thread>

#include "tbb/task.h"

#include "counter.h"
#include "relocator.h"

namespace TBBSort
{
    class Sorter : public tbb::task
    {
        protected:
        int* p_first;
        int* p_last;
        const size_t c_threads_count;

        public:
        Sorter(int* first, int* last, size_t threads_count = std::thread::hardware_concurrency());
        ~Sorter() = default;

        tbb::task* execute();
    };

    void tbbSort(int* first, int* last, size_t threads_count = std::thread::hardware_concurrency());
}

