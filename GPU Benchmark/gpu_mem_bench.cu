#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <cuda.h>
#define TOTAL_MEMORY 1
#define BLOCK_SIZE 104876
//__global__ void add( int *a, int *b, int *c ) {
// int tid = blockIdx.x*blockDim.x+threadIdx.x; // handle the data at this index
//   c[tid] = a[tid] + b[tid];
 
//}

int main( void ) {
double time_s;
long start_time,end_time;
char *a;
struct timeval start,stop;
char *dev_a;
a=(char*)malloc(BLOCK_SIZE * sizeof(char));
memset(a,'$',BLOCK_SIZE);
int k;
 // allocate the memory on the GPU
cudaMalloc( (void**)&dev_a, BLOCK_SIZE * sizeof(char) );
gettimeofday(&start,NULL);
start_time=start.tv_sec*1000000 + start.tv_usec;//get start time
for(k=0;k<(TOTAL_MEMORY/BLOCK_SIZE);k++)
cudaMemcpy( dev_a, a, BLOCK_SIZE * sizeof(char),cudaMemcpyHostToDevice );
gettimeofday(&stop,NULL);
end_time=stop.tv_sec*1000000 + stop.tv_usec;//get end time

// add<<<blocks,threads>>>( dev_a, dev_b, dev_c );
time_s=end_time-start_time;
printf("Time taken: %lf",(time_s));
printf("Throughput: %lf GB/s",(double)(TOTAL_MEMORY)/(time_s*1000));
// free the memory allocated on the GPU
 cudaFree( dev_a );
 return 0;
}

