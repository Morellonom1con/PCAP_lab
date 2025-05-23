#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    char word[50];
    MPI_Status status;
    if (rank==0)
    {
        printf("Enter a word:");
        fgets(word,50,stdin);
        MPI_Ssend(word,50,MPI_CHAR,1,0,MPI_COMM_WORLD);
    }
    if(rank==1)
    {
        MPI_Recv(word,50,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
        for(int i=0;i<50;i++)
        {
            if (word[i]>='A' && word[i]<='Z')
            {
                word[i]+=32;
            }
            else if (word[i]>='a' && word[i]<='z')
            {
                word[i]-=32;
            }
        }
        MPI_Ssend(word,50,MPI_CHAR,0,1,MPI_COMM_WORLD);
    }
    if(rank==0)
    {
        MPI_Recv(word,50,MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
        printf("Recieved word is: ");
        puts(word);
    }
    MPI_Finalize();
    return 0;
}