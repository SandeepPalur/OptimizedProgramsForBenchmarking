#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <cuda.h>
#define NUM_CYCLES 50

__global__ void add( int *a, int *b, int *c ) {
 int tid = blockIdx.x*blockDim.x+threadIdx.x; // handle the data at this index
   c[tid]=a[tid] + b[tid];
   a[tid]=a[tid] + b[tid];
   c[tid]=a[tid] + b[tid];

 
}

int main( void ) {
int deviceCount, device;
int blocks,threads,n;
double time_s;
long start_time,end_time;
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
            blocks=properties.multiProcessorCount;
            threads=properties.maxThreadsPerMultiProcessor;
            n=properties.multiProcessorCount * properties.maxThreadsPerMultiProcessor;
    }
}
a=(int*)malloc(n * sizeof(int));
b=(int*)malloc(n * sizeof(int));
c=(int*)malloc(n * sizeof(int));

 // allocate the memory on the GPU
cudaMalloc( (void**)&dev_a, n * sizeof(int) );
cudaMalloc( (void**)&dev_b, n * sizeof(int) );
cudaMalloc( (void**)&dev_c, n * sizeof(int) );
 // fill the arrays 'a' and 'b' on the CPU
 for (int i=0; i<n; i++) {
 a[i] = 23434;
 b[i] = i * i;
 }
cudaMemcpy( dev_a, a, n * sizeof(int),cudaMemcpyHostToDevice );
cudaMemcpy( dev_b, b, n * sizeof(int),cudaMemcpyHostToDevice );
gettimeofday(&start,NULL);
int l;
start_time=start.tv_sec*1000000 + start.tv_usec;//get start time
for(l=0;l<NUM_CYCLES;l++)
 add<<<blocks,threads>>>( dev_a, dev_b, dev_c );
gettimeofday(&stop,NULL);
end_time=stop.tv_sec*1000000 + stop.tv_usec;//get end time
 // copy the array 'c' back from the GPU to the CPU
cudaMemcpy( c, dev_c, n * sizeof(int),cudaMemcpyDeviceToHost );
 // display the results
// for (int i=0; i<N; i++) {
// printf( "%d + %d = %d\n", a[i], b[i], c[i] );
// }
 // free the memory allocated on the GPU
time_s=end_time-start_time;
printf("Time taken: %lf",time_s);
printf("GFLOPS: %lf",(double)(NUM_CYCLES*n*3)/(time_s*1000));

 cudaFree( dev_a );
 cudaFree( dev_b );
 cudaFree( dev_c );
 return 0;
}

