#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "image.h"
#include "sobel_block.h"
#include "mpi_utils.h"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    int size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int width = 0;
    int height = 0;

    unsigned char *pixels = NULL;


    if (rank == 0)
    {
        Image *img = loadPGM("images/entrada.pgm");

        if (img == NULL)
        {
            printf("Erro ao carregar imagem\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        width = img->width;
        height = img->height;

        pixels = img->pixels;


        printf("Imagem: %dx%d\n",
               width,
               height);

        printf("Processos: %d\n",
               size);
    }


    MPI_Bcast(
        &width,
        1,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    MPI_Bcast(
        &height,
        1,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    int *sendCounts = NULL;
    int *displacements = NULL;
    int *lineCounts = NULL;

    if (rank == 0)
    {
	sendCounts = malloc(size * sizeof(int));
	displacements = malloc(size * sizeof(int));
	lineCounts = malloc(size * sizeof(int));

        int base = height / size;
        int resto = height % size;


        int offset = 0;


        for (int i = 0; i < size; i++)
        {
            int linhas = base;

            if (i < resto)
                linhas++;

	    lineCounts[i] = linhas;

            sendCounts[i] = linhas * width;

            displacements[i] = offset;

            offset += linhas * width;
        }
    }


    int localHeight;


    MPI_Scatter(
        lineCounts,
        1,
        MPI_INT,
        &localHeight,
        1,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );


    unsigned char *localInput =
        malloc((size_t)(localHeight + 2) * width);


    unsigned char *localOutput =
        malloc((size_t)localHeight * width);
   

    MPI_Scatterv(
        pixels,
        sendCounts,
        displacements,
        MPI_UNSIGNED_CHAR,

        &localInput[width],
        localHeight * width,
        MPI_UNSIGNED_CHAR,

        0,
        MPI_COMM_WORLD
    );    


    exchangeHalos(
        localInput,
        width,
        localHeight,
        rank,
        size
    );


    applySobelBlock(
        localInput,
        localOutput,
        width,
        localHeight
    );

unsigned char *output = NULL;

if (rank == 0)
{
    output = malloc((size_t)height * width);
}


    MPI_Gatherv(
        localOutput,
        localHeight * width,
        MPI_UNSIGNED_CHAR,

        output,
        sendCounts,
        displacements,
        MPI_UNSIGNED_CHAR,

        0,
        MPI_COMM_WORLD
    );

if (rank == 0)
{
    Image result;

    result.width = width;
    result.height = height;
    result.maxValue = 255;
    result.pixels = output;


    savePGM(
        "output/sobel_mpi.pgm",
        &result
    );


    printf("Imagem salva em output/sobel_mpi.pgm\n");


    free(output);
    free(sendCounts);
    free(displacements);
    free(lineCounts);
}

    free(localInput);
    free(localOutput);


    if (rank == 0)
    {
        free(pixels);
    }


    MPI_Finalize();

    return 0;
}
