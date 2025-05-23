#include<mpi.h>
#include<stdio.h>

int main(int argc,char*argv[])
{
    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    char word[6]="HELLO";
    if (size>5){
        printf("number of processes is more than number of letters in the word");
        return 0;
    }
    printf("rank:%d\n",rank);
    word[rank]+=32;
    puts(word);
    MPI_Finalize();
    return 0;
}