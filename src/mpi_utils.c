#include "mpi_utils.h"


void exchangeHalos(
    unsigned char *localData,
    int width,
    int localHeight,
    int rank,
    int size
)
{
    MPI_Status status;


    // Envia a última linha para o processo abaixo
    // e recebe a linha acima do processo anterior

    if (rank > 0)
    {
        MPI_Sendrecv(
            &localData[width],
            width,
            MPI_UNSIGNED_CHAR,
            rank - 1,
            0,

            localData,
            width,
            MPI_UNSIGNED_CHAR,
            rank - 1,
            0,

            MPI_COMM_WORLD,
            &status
        );
    }


    // Envia a última linha para o processo abaixo
    // e recebe a linha abaixo

    if (rank < size - 1)
    {
        MPI_Sendrecv(
            &localData[localHeight * width],
            width,
            MPI_UNSIGNED_CHAR,
            rank + 1,
            0,

            &localData[(localHeight + 1) * width],
            width,
            MPI_UNSIGNED_CHAR,
            rank + 1,
            0,

            MPI_COMM_WORLD,
            &status
        );
    }
}
