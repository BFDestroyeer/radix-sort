#include "tbbsort.h"

void tbbSort(int* first, int* last, size_t threads_count)
{
    TBBSort::Sorter& sorter = *new(tbb::task::allocate_root()) TBBSort::Sorter(first, last, threads_count);
    tbb::task::spawn_root_and_wait(sorter);
}