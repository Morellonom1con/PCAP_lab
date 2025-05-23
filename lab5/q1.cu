#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>

__global__ void vectorAdd(float *A, float *B, float *C, int N) {
    int idx = blockIdx.x * blockDim.x + t hreadIdx.x;
    if (idx < N) {
        C[idx] = A[idx] + B[idx];
    }
}

int main() {
    int N;
    
    printf("Enter the length of the vectors: \n");
    scanf("%d",&N);
    int size=N*sizeof(float);

    float h_A[N],h_B[N],h_C[N];

    printf("Enter vector A: \n");
    for (int i = 0; i < N; i++) {
        scanf("%f",&h_A[i]);
    }

    printf("Enter vector B: \n");
    for (int i = 0; i < N; i++) {
        scanf("%f",&h_B[i]);
    }

    float *d_A, *d_B, *d_C;
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    int blockSize = N;// for b) its some blocksize say 256
    int gridSize = 1;// and gridsize (N-1)/blocksize+1

    vectorAdd<<<gridSize, blockSize>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\nVector C :\n");
    for (int i=0; i< N;i++)
    {
        printf("%f ",h_C[i]);
    }
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
