#pragma once

#ifdef linux
#include <cstring>
#endif

#include <mpi.h>

void mpiSort(int* first, int* last, int rank);
