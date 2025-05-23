#include<mpi.h>
#include<stdio.h>

int main(int argc,char* argv[])
{
    int size,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if ( rank%2==0)
    {
        printf("rank:%d \n",rank);
        printf("Hello\n");
    }
    else{
        printf("rank:%d \n",rank);
        printf("World\n");
    }
    MPI_Finalize();
    return 0;
}