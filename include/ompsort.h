#pragma once

#include <cstring>

#include <omp.h>

/**
 * @brief Sort algorithm for Little endian on OpenMP
 * 
 * @param first array first element pointer
 * @param last array last element pointer
 */
void ompSort(int* first, int* last);
