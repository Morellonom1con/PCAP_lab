#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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
        int buffer_size=MPI_BSEND_OVERHEAD+size-1;
        int *buffer =(int*)malloc(buffer_size*sizeof(int));
        MPI_Buffer_attach(buffer,buffer_size);
        num=(int*)malloc(size*sizeof(int));
        printf("Enter numbers for each process : \n");
        for (int i=1;i<size;i++)
        {
            scanf("%d",num+i);
        }
        for (int i=1;i<size;i++)
        {
            MPI_Bsend(num+i,1,MPI_INT,i,0,MPI_COMM_WORLD);
        }
        MPI_Buffer_detach(&buffer,&buffer_size);
    }
     if (rank!=0)
    {
        num=(int*)malloc(sizeof(int));
        MPI_Recv(num,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        int val=*num;
        if (rank%2==0)
        {
            val=pow(val,2);
            printf("\nrank %d : %d",rank,val);
        }
        else{
            val=pow(val,3);
            printf("\nrank %d : %d",rank,val);
        }
    }
    MPI_Finalize();
    return 0;
}