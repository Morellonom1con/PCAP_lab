#include<mpi.h>
#include<stdio.h>

int main(int argc, char* argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int a=3,b=4;
    if (rank==0){
        if(size>4)
        {
            printf("Run the program with four or less processes ");
            return 0;
        }
        else{     
            printf("Addition:\n");
            printf("%d+%d=%d\n",a,b,a+b);
        }
    }
    if (rank==1)
    {
        printf("Subtraction:\n");
        printf("%d-%d=%d\n",a,b,a-b);    }
    if (rank==2)
    {
        printf("Multiplication:\n");
        printf("%d*%d=%d\n",a,b,a*b);    }
    if (rank==3)
    {
        printf("Division:\n");
        printf("%d/%d=%d\n",a,b,a/b);    }
MPI_Finalize();
return 0;
}