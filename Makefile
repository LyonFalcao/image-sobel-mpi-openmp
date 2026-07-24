	CC = mpicc

CFLAGS = -Wall -Wextra -O2 -fopenmp

SRC = src/main_mpi.c \
      src/image.c \
      src/sobel_block.c \
      src/mpi_utils.c

TARGET = imageproc_mpi


all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
