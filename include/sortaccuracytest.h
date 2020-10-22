#pragma once

#include <iostream>

#include "mpi.h"

#include "functions.h"
#include "mpisort.h"
#include "ompsort.h"
#include "recursivesequentialsort.h"
#include "sequentialsort.h"
#include "tbbsort.h"
#include "threadsort.h"

bool sorted(int* begin, int* end);

/**
 * @brief Acuracy test for all sorting algorithms
 * 
 * @param size Size of array be used for testing
 * @note It's output results to console 
 */
void sortAccuracyTest(size_t size);

