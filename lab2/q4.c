#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char*argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int num;
    MPI_Status status;
    if (rank==0)
    {
        printf("Enter a number :");
        scanf("%d",&num);
        MPI_Send(&num,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    }
    for (int i=1;i<size-1;i++)
    {   
        if (rank==i)
        {
            MPI_Recv(&num,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
            num+=1;
            MPI_Send(&num,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        }
    }
    if(rank==size-1)
    {
        MPI_Recv(&num,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
        num+=1;
        MPI_Send(&num,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    if(rank==0)
    {
        MPI_Recv(&num,1,MPI_INT,size-1,0,MPI_COMM_WORLD,&status);
        printf("Value of num after the traversal : %d" ,num);
    }
    MPI_Finalize();
    return 0;
}