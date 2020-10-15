#pragma once

#include <cstring>
#include <thread>

#include <omp.h>

/**
 * @brief Sort algorithm for Little endian on OpenMP
 * 
 * @param first array first element pointer
 * @param last array last element pointer
 * @param threads_count count of threads
 */
void ompSort(int* first, int* last, size_t threads_count = std::thread::hardware_concurrency());
