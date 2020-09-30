#pragma once

#include "time.h"

#include <random>

void fullWhitRandom(int* array, size_t size);

/**
 * @brief Function to swap negative elements of arrat with positive
 * 
 * @param first array last element pointer
 * @param last  order of compared digit
 */
void relocateNegatives(int* first, int* last);