#include<mpi.h>
#include<stdio.h>
#include<math.h>
int main(int argc,char*argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int x=2;
    int val=pow(x,rank);
    printf("the rank of this process is %d and the value of the %d^%d is %d",rank,x,rank,val);
    printf("\n");
    MPI_Finalize();
    return 0;
}