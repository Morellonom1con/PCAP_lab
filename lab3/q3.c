#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char*argv[])
{
    int size,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    char a[100],b[100];
    int M;
    int anv[size];
    if (rank==0){
        printf("Enter a string(length should be evenly divisible by number of processes):");
        fgets(a,50,stdin);
        M=strlen(a)/size;
    }
    MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(a,M,MPI_CHAR,b,M,MPI_CHAR,0,MPI_COMM_WORLD);
    int nv=0;
    for(int i=0;i<M;i++)
    {
        if(b[i]!='a' &&  b[i]!='e' && b[i]!='i' && b[i]!='o' && b[i]!='u' && b[i]!='A' && b[i]!='E' && b[i]!='I' && b[i]!='O' && b[i]!='U'){
            nv+=1;
        }
    }
    MPI_Gather(&nv,1,MPI_INT,anv,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        int t_nv=0;
        for(int i=0;i<size;i++)
        {
            printf("\nprocess %d \nnon vowels : %d",i,anv[i]);
            t_nv+=anv[i];
        }
        printf("\ntotal number of non vowels : %d",t_nv);
    }
MPI_Finalize();
return 0;
}