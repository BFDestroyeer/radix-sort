#include "mpisort.h"

void mpiSort(int* first, int* last, int rank)
{
    uint64_t size = last - first + 1;
    MPI_Bcast(&size, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
    int process_count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    int* send_counts = new int[process_count]();
    int* send_displs = new int[process_count]();
    size_t current_size = 0;
    for (size_t i = 0; i < process_count - 1; i++)
    {
        send_counts[i] = (int) (size / process_count);
        send_displs[i] = (int) current_size;
        current_size += send_counts[i];
    }
    send_counts[process_count - 1] = (int) (size - (size / process_count) * (process_count - 1));
    send_displs[process_count - 1] = (int) current_size;
    for (size_t i = 0; i < sizeof(int); i++)
    {
        //Counting
        int* buffer = new int[send_counts[rank]]();
        MPI_Scatterv(first, send_counts, send_displs,MPI_INT, buffer, send_counts[rank], MPI_INT, 0, MPI_COMM_WORLD);
        uint64_t counts[256] = {};
        for (int* j = buffer; j < buffer + send_counts[rank]; j++)
        {
            counts[*((unsigned char*) j + i)]++;
        }
        uint64_t* total_counts = nullptr;
        if (rank == 0)
        {
            total_counts = new uint64_t[256 * process_count];
        }
        //Calculating offset
        MPI_Gather(counts, 256, MPI_UINT64_T, total_counts, 256, MPI_UINT64_T, 0, MPI_COMM_WORLD);
        if (rank == 0)
        {
            size_t summ = 0;
            for (size_t j = 0; j < 256; j++)
            {
                for (size_t k = 0; k < process_count; k++)
                {
                    size_t temp = total_counts[j + k * 256];
                    total_counts[j + k * 256] = summ;
                    summ += temp;
                }
            }
        }
        MPI_Scatter(total_counts, 256, MPI_UINT64_T, counts, 256, MPI_UINT64_T, 0, MPI_COMM_WORLD);
        //Calculating destination
        uint64_t* destination = new uint64_t[send_counts[rank]]();
        for (size_t j = 0; j < send_counts[rank]; j++)
        {
            destination[j] = counts[*(((unsigned char*) (buffer + j)) + i)]++;
        }
        uint64_t* total_destination = nullptr;
        if (rank == 0)
        {
            total_destination = new uint64_t[size];
        }
        MPI_Gatherv(destination, send_counts[rank], MPI_UINT64_T, total_destination, send_counts, send_displs, MPI_UINT64_T, 0, MPI_COMM_WORLD);
        delete[] buffer;
        delete[] destination;
        delete[] total_counts;
        //Relocating
        if (rank == 0)
        {
            int* stage_result = new int[size];
            for (size_t j = 0; j < size; j++)
            {
                stage_result[total_destination[j]] = first[j];
            }
            for (size_t j = 0; j < size; j++)
            {
                first[j] = stage_result[j];
            }
            delete[] stage_result;
        }
        delete[] total_destination;
    }
    delete[] send_counts;
    delete[] send_displs;
}
