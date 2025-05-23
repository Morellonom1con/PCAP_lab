#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc , char* argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    int fact=1;
    for (int i=0;i<rank;i++)
    {
        fact*=i+1;
    }
    int f_sum;
    int err;
    err=MPI_SUCCESS;
    if(size==3)
    err=MPI_Scan(&fact,&f_sum,1,MPI_INT,MPI_SUM,MPI_COMM_NULL);
    MPI_Scan(&fact,&f_sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    if(err!=MPI_SUCCESS)
    {
        if(rank==0)
        printf("Error Handled for size==3, TERMINATING PROGRAM\n");
        return 0;
    }
    if (rank==size-1)
    {
        printf("Sum of factorials till N: %d\n",f_sum);
    }
    MPI_Finalize();
    return 0;
}