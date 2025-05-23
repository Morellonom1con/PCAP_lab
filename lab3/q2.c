#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char*argv[])
{
    int size,rank;
    int M;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if (rank==0){
        printf("Enter the value of M:");
        scanf("%d",&M);
    }
    MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
    int a[size*M],b[size],c[M];
    if (rank==0){
        printf("Enter the nxM values :");
        for(int i=0;i<size*M;i++)
        {
            scanf("%d",&a[i]);
        }
    }
    MPI_Scatter(a,M,MPI_INT,b,M,MPI_INT,0,MPI_COMM_WORLD);
    int avg=0;
    for(int i=0;i<M;i++)
    {
        avg+=b[i];
    }
    avg/=M;
    MPI_Gather(&avg,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        int t_avg=0;
        for(int i=0;i<size;i++)
        {
            t_avg+=b[i];
        }
        printf("total average : %d \n",t_avg);
        t_avg/=size;
        printf("average of averages : %d",t_avg);
    }
MPI_Finalize();
return 0;
}