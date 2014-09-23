#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda.h>

main(){
int deviceCount, device;
//int gpuDeviceCount = 0;
struct cudaDeviceProp properties;
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
    }
}
}
