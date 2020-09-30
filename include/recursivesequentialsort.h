#pragma once

#include <iterator>

/**
 * @brief Recursive sequential radix sort
 * 
 * @param first array first element pointer
 * @param last  array last element pointer
 */
void recursiveSequentialSort(int* first, int* last);

/**
 * @brief Recursive sequential radix sort stage
 * 
 * @param first array first element pointer
 * @param last  array last element pointer
 * @param order order of compared digit
 */
void recursiveSequentialSortStage(int* first, int* last, size_t order);
