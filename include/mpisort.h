#pragma once

#include <cstring>

#include <mpi.h>

/**
 * @brief Sort algorithm for Little endian on MPI
 * 
 * @param first Array first element pointer (Unused for not root process)
 * @param last Array last element pointer(Unused for not root process)
 * @param comunicator Communicator with all processes
 */
void mpiSort(int* first, int* last, MPI_Comm comunicator = MPI_COMM_WORLD);
