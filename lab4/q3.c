#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc , char* argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int a[4*4],b[4],c[4];
    if(rank==0)
    {
        printf("Enter values for a 4x4 matrix: \n");
        for(int j=0;j<4;j++)
        {
            for(int i=0; i<4;i++)
            {
                scanf("%d",&a[j*4+i]);
            }
        }
    }
    MPI_Scatter(a,4,MPI_INT,b,4,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scan(b,c,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    MPI_Gather(c,4,MPI_INT,a,4,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        printf("\nMatrix: \n");
        for(int j=0;j<4;j++)
        {
            for(int i=0; i<4;i++)
            {
                printf("%d ",a[j*4+i]);
            }
            printf("\n");
        }
    }
}