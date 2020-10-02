#pragma once

#include "time.h"

#include <random>

/**
 * @brief Fill array with random values
 * 
 * @param array Array first element pointer
 * @param size Array last element pointer
 */
void fillWhitRandom(int* array, size_t size);

/**
 * @brief Function to swap negative elements of arrat with positive
 * 
 * @param first Array first element pointer
 * @param last  Array last element pointer
 */
void relocateNegatives(int* first, int* last);