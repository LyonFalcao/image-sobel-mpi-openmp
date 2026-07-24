#ifndef MPI_UTILS_H
#define MPI_UTILS_H

#include <mpi.h>

void exchangeHalos(
    unsigned char *localData,
    int width,
    int localHeight,
    int rank,
    int size
);

#endif

