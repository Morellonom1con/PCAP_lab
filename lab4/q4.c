#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char word[size + 1];
    char send_char, recv_buffer[size];
    if (rank == 0) {
        printf("Enter a word of length %d: ", size);
        scanf("%s", word);
    }
    MPI_Scatter(word, 1, MPI_CHAR, &send_char, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = 0; i < size; i++)
        recv_buffer[i] = (i < rank + 1) ? send_char : '\0';

    char gather_buffer[size * size];
    MPI_Gather(recv_buffer, size, MPI_CHAR, gather_buffer, size, MPI_CHAR, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Output: ");
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < r + 1; c++) {
                printf("%c", gather_buffer[r * size + c]);
            }
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}