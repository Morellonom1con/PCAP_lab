#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int a[size],b[size],c;
    if (rank==0)
    {
        printf("Enter a value for each process running: ");
        for(int i=0;i<size;i++)
        {
            scanf("%d",a+i);
        }
    }
    int fact=1;
    MPI_Scatter(a,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=1;i<=c;i++)
    {
        fact *=i;
    }
    MPI_Gather(&fact,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        int sum=0;
        for(int i=0;i<size;i++)
        {
            sum+=b[i];
        }
        printf("Sum: %d",sum);
    }
    MPI_Finalize();
    return 0;
}