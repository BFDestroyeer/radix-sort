#pragma once

#ifdef linux
#include <cstring>
#endif

#include <thread>

/**
 * @brief Sort algorithm for Little endian on C++ threads
 * 
 * @param first array first element pointer
 * @param last array last element pointer
 * @param threads_count count of threads
 */
void threadSort(int* first, int* last, size_t threads_count = std::thread::hardware_concurrency());

/**
 * @brief
 * 
 * @param first array first element pointer
 * @param last array last element pointer
 * @param byte_number number of byte to check
 * @param counts 
 */
void counter(int* first, int* last, size_t byte_number, size_t* counts);

/**
 * @brief 
 * 
 * @param first array first element pointer 
 * @param last arrat last element pointer
 * @param offsets array of offsets
 * @param byte_number 
 * @param destination destination array pointer
 */
void relocator(int* first, int* last, size_t* offsets, size_t byte_number, int* destination);