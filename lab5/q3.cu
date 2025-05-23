#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>
#include<math.h>

__global__ void Sine(float *A, float *C, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N) {
        C[idx] = sin(A[idx]);
    }
}

int main() {
    int N;
    
    printf("Enter the number of angles: \n");
    scanf("%d",&N);
    int size=N*sizeof(float);

    float h_A[N],h_C[N];

    printf("Enter Array of radian angles: \n");
    for (int i = 0; i < N; i++) {
        scanf("%f",&h_A[i]);
    }

    float *d_A, *d_C;
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (N-1)/blockSize+1;

    Sine<<<gridSize, blockSize>>>(d_A, d_C, N);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\nSine of angles :\n");
    for (int i=0; i< N;i++)
    {
        printf("%f ",h_C[i]);
    }
    cudaFree(d_A);
    cudaFree(d_C);
    return 0;
}
