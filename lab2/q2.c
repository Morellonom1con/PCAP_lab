#include<mpi.h>
#include<stdio.h>
#include <stdlib.h>
int main(int argc , char* argv[])
{
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int *num;
    MPI_Status status;
    if(rank==0)
    {
        num=(int*)malloc(size*sizeof(int));
        printf("Enter numbers for each process : \n");
        for (int i=1;i<size;i++)
        {
            scanf("%d",num+i);
        }
        for (int i=1;i<size;i++)
        {
            MPI_Send(num+i,1,MPI_INT,i,0,MPI_COMM_WORLD);
        }
    }
     if (rank!=0)
    {
        num=(int*)malloc(sizeof(int));
        MPI_Recv(num,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        printf("\nrank %d : %d",rank,*num);
    }
    MPI_Finalize();
    return 0;
}