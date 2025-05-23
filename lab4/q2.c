#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc , char* argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int a[3*3],b[3],s;
    if(rank==0)
    {
        printf("Enter values for a 3x3 matrix: \n");
        for(int j=0;j<3;j++)
        {
            for(int i=0; i<3;i++)
            {
                scanf("%d",&a[j*3+i]);
            }
        }
        printf("Enter the search element: \n");
        scanf("%d",&s);
    }
    MPI_Bcast(&s,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(a,3,MPI_INT,b,3,MPI_INT,0,MPI_COMM_WORLD);
    int nos=0;
    for (int i=0;i<3;i++)
    {
        if(b[i]==s)
        {
            nos+=1;
        }
    }
    int snos=0;
    MPI_Reduce(&nos,&snos,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        printf("Number of matches in the matrix: %d",snos);
    }
    MPI_Finalize();
    return 0;
}