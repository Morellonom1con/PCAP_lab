#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__global__ void find(const char *arr, int la, const char *word, int lw, int *ans) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i + lw <= la) {
        bool match = true;
        for (int j = 0; j < lw; ++j) {
            if (arr[i + j] != word[j]) {
                match = false;
                break;
            }
        }
        if (match) atomicAdd(ans, 1);
    }
}

int main() {
    int la, lw, ans = 0;
    char *arr, *word, *darr, *dword;
    int *dans;

    printf("Enter string length: ");
    scanf("%d%*c", &la);
    arr = (char *)malloc(la + 1);
    printf("Enter string: ");
    fgets(arr, la + 1, stdin);

    printf("Enter word length: ");
    scanf("%d%*c", &lw);
    word = (char *)malloc(lw + 1);
    printf("Enter word: ");
    fgets(word, lw + 1, stdin);

    cudaMalloc(&darr, la + 1);
    cudaMalloc(&dword, lw + 1);
    cudaMalloc(&dans, sizeof(int));
    cudaMemcpy(darr, arr, la + 1, cudaMemcpyHostToDevice);
    cudaMemcpy(dword, word, lw + 1, cudaMemcpyHostToDevice);
    cudaMemset(dans, 0, sizeof(int));

    int threads = 256, blocks = (la + threads - 1) / threads;
    find<<<blocks, threads>>>(darr, la, dword, lw, dans);

    cudaMemcpy(&ans, dans, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Occurrences: %d\n", ans);

    free(arr); free(word);
    cudaFree(darr); cudaFree(dword); cudaFree(dans);
    return 0;
}
