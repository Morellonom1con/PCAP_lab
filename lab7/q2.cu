#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__global__ void newstring(const char *inp, char *ans, int l) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < l) {
        int copy = l - i;
        int j = (l * (l + 1)) / 2 - (copy * (copy + 1)) / 2;
        for (int k = 0; k < copy; ++k)
            ans[j + k] = inp[k];
    }
}

int main() {
    int l;
    printf("Enter word length: ");
    scanf("%d", &l);
    char *arr = (char *)malloc(l + 1);
    printf("Enter word: ");
    scanf("%s", arr);
    int total = (l * (l + 1)) / 2;
    char *ans = (char *)malloc(total + 1);
    char *darr, *dans;
    cudaMalloc(&darr, l + 1);
    cudaMalloc(&dans, total + 1);
    cudaMemcpy(darr, arr, l + 1, cudaMemcpyHostToDevice);
    newstring<<<(l + 255) / 256, 256>>>(darr, dans, l);
    cudaMemcpy(ans, dans, total + 1, cudaMemcpyDeviceToHost);
    ans[total] = '\0';
    printf("%s\n", ans);
    free(arr); free(ans);
    cudaFree(darr); cudaFree(dans);
    return 0;
}
