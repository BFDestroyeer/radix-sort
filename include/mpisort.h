#pragma once

#ifdef linux
#include <cstring>
#endif

#include <mpi.h>

void mpiSort(int* first, int* last, size_t size, int rank);
