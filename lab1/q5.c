#include<mpi.h>
#include<stdio.h>

int main(int argc,char*argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if (rank%2==0)
    {
        int fact=1;
        for (int i=1;i<=rank;i++)
        {
            fact*=i;
        }
        printf("rank:%d\nfactorial of rank:%d\n", rank,fact);
        
    }
    else{
        int prev1=0;
        int prev2=0;
        int fib=1;
        for (int i=1;i<rank;i++)
        {
            prev2=prev1;
            prev1=fib;
            fib=prev1+prev2;
        }
        printf("rank:%d\nfibonacci number of rank:%d\n", rank,fib);
    }
    MPI_Finalize();
    return 0;
}