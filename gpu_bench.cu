#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <cuda.h>
//#include "cuda_runtime_api.h"
//#define N 23040*10

__global__ void add( int *a, int *b, int *c ) {
 int tid = blockIdx.x*blockDim.x+threadIdx.x; // handle the data at this index
// if (tid < N)
 c[tid] = a[tid] + b[tid];
}

int main( void ) {
int deviceCount, device;
int B,T,N;
struct cudaDeviceProp properties;
int *a, *b, *c;
struct timeval start,stop;
int *dev_a, *dev_b, *dev_c;
cudaError_t cudaResultCode = cudaGetDeviceCount(&deviceCount);
if (cudaResultCode != cudaSuccess)
    deviceCount = 0;
/* machines with no GPUs can still report one emulation device */
for (device = 0; device < deviceCount; ++device) {
    cudaGetDeviceProperties(&properties, device);
    if (properties.major != 9999) /* 9999 means emulation only */
    if (device==0)
    {
            printf("multiProcessorCount %d\n",properties.multiProcessorCount);
            printf("maxThreadsPerMultiProcessor %d\n",properties.maxThreadsPerMultiProcessor);
            B=properties.multiProcessorCount;
            T=properties.maxThreadsPerMultiProcessor;
            N=10*properties.multiProcessorCount * 10*properties.maxThreadsPerMultiProcessor;
    }
}
a=(int*)malloc(N * sizeof(int));
b=(int*)malloc(N * sizeof(int));
c=(int*)malloc(N * sizeof(int));

 // allocate the memory on the GPU
cudaMalloc( (void**)&dev_a, N * sizeof(int) );
cudaMalloc( (void**)&dev_b, N * sizeof(int) );
cudaMalloc( (void**)&dev_c, N * sizeof(int) );
 // fill the arrays 'a' and 'b' on the CPU
 for (int i=0; i<N; i++) {
 a[i] = -i;
 b[i] = i * i;
 }
cudaMemcpy( dev_a, a, N * sizeof(int),cudaMemcpyHostToDevice );
cudaMemcpy( dev_b, b, N * sizeof(int),cudaMemcpyHostToDevice );
gettimeofday(&start,NULL);
 add<<<B*10,T*10>>>( dev_a, dev_b, dev_c );
gettimeofday(&stop,NULL);
 // copy the array 'c' back from the GPU to the CPU
cudaMemcpy( c, dev_c, N * sizeof(int),cudaMemcpyDeviceToHost );
 // display the results
// for (int i=0; i<N; i++) {
// printf( "%d + %d = %d\n", a[i], b[i], c[i] );
// }
 // free the memory allocated on the GPU
printf("Time elapsed is:%ld\n", (stop.tv_usec-start.tv_usec));
 cudaFree( dev_a );
 cudaFree( dev_b );
 cudaFree( dev_c );
 return 0;
}

