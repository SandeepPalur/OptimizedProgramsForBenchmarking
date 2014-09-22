#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#define NUM_THREADS 64
long start_times[NUM_THREADS];
long end_times[NUM_THREADS];
long start_times_iop[NUM_THREADS];
long end_times_iop[NUM_THREADS];
void *ComputeFlops(void *threadid)
{
   long tid;
   int i;
   float result,n1=3.5455f,n2=12.423f,n3=145.345f,n4=123.238f,n5=11.447f;
double sum1=0.1, sum2=-0.1, sum3=0.2, sum4=-0.2, sum5=0.0,add=0.1,sum0=0.1, sum6=-0.1, sum7=0.2, sum8=-0.2, sum9=0.0,sum10=0.1, sum11=0.1, sum12=0.2, sum13=0.3, sum14=0.0;
   double mul1=1.0, mul2= 1.1, mul3=1.2, mul4= 1.3, mul5=1.4,mul=1.1,mul0=1.0, mul6= 1.1, mul7=1.2, mul8= 1.3, mul9=1.4,mul10=1.1,mul11=1.2,mul12=1.0,mul13=1.1,mul14=1.2;
   struct timeval start,stop;
   tid = (long)threadid;
   gettimeofday(&start,NULL);
   start_times[tid]=start.tv_sec*1000000 + start.tv_usec;
//   printf("start times %ld",start_times[tid]);

   //for flops
   for(i=0;i<10000000000/(30*NUM_THREADS);i++){
   /*mul1*mul; mul2*mul; mul3*mul;
      sum1+add; sum2+add; sum3+add;
      mul4*mul; mul5*mul; mul12*mul;
      sum4+add; sum5+add; sum0+add;

      mul13*mul; mul14*mul; mul0*mul;
      sum6+add; sum7+add; sum8+add;
      mul6*mul; mul7*mul; mul8*mul;
      sum9+add; sum10+add; sum11+add;

      mul9*mul; mul10*mul; mul11*mul;
      sum12+add; sum13+add; sum14+add;  */

   mul1*mul; mul2*mul; mul3*mul;
      sum1+add; sum2+add; sum3+add;
      mul4*mul; mul5*mul; mul1*mul;
      sum4+add; sum5+add; sum1+add;

      mul2*mul; mul3*mul; mul4*mul;
      sum2+add; sum3+add; sum4+add;
      mul5*mul; mul1*mul; mul2*mul;
      sum5+add; sum1+add; sum2+add;

      mul3*mul; mul4*mul; mul5*mul;
      sum3+add; sum4+add; sum5+add;      
      
   }

   gettimeofday(&stop,NULL);
   end_times[tid]=stop.tv_sec*1000000 + stop.tv_usec;

   // printf("tid:%ld Time elapsed:%ld %ld %ld\n",tid,start.tv_usec,stop.tv_usec, stop.tv_usec-start.tv_usec);
   printf("time elapsed:%ld",(stop.tv_sec*1000000 + stop.tv_usec) - (start.tv_sec*1000000 + start.tv_usec));
   pthread_exit(NULL);
}

void *ComputeIops(void *threadid)
{
   long tid;
   int i;
 int sum1=1, sum2=-2, sum3=1, sum4=-2, sum5=1,add=0,sum0=2, sum6=1, sum7=1, sum8=-2, sum9=-1,sum10=1, sum11=1, sum12=2, sum13=-1, sum14=1;
   int mul1=1, mul2= 1, mul3=1, mul4= 1, mul5=1,mul=1,mul0=1, mul6= 1, mul7=1, mul8= 1, mul9=1,mul10=1,mul11=1,mul12=1,mul13=1,mul14=1;
  struct timeval start_iop,stop_iop;
   tid = (long)threadid;
   gettimeofday(&start_iop,NULL);
   start_times_iop[tid]=start_iop.tv_sec*1000000 + start_iop.tv_usec;
  // printf("start times %ld",start_times[tid]);

   //for iops
   for(i=0;i<10000000000/(30*NUM_THREADS);i++){
    mul1*mul; mul2*mul; mul3*mul;
      sum1+add; sum2+add; sum3+add;
      mul4*mul; mul5*mul; mul1*mul;
      sum4+add; sum5+add; sum1+add;

      mul2*mul; mul3*mul; mul4*mul;
      sum2+add; sum3+add; sum4+add;
      mul5*mul; mul1*mul; mul2*mul;
      sum5+add; sum1+add; sum2+add;

      mul3*mul; mul4*mul; mul5*mul;
      sum3+add; sum4+add; sum5+add;  

 

  

   }
   gettimeofday(&stop_iop,NULL);
   end_times_iop[tid]=stop_iop.tv_sec*1000000 + stop_iop.tv_usec;

   //printf("time elapsed:%ld",(stop_iop.tv_sec*1000000 + stop_iop.tv_usec) - (start_iop.tv_sec*1000000 + start_iop.tv_usec));
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS],threads_iops[NUM_THREADS];
   int rc;
   long t,start,start_iop,end,end_iop,j;
   double flops_total_time,iops_total_time;
   for(t=0; t<NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, ComputeFlops, (void *)t);
   }
    //wait for all child threads to finish
    for(t=0; t<NUM_THREADS; t++){
	pthread_join(threads[t],NULL);
    }
start=start_times[0];
  end=end_times[0];
for(j=1;j<NUM_THREADS;j++)
  {
  	if(start_times[j]< start)
   		start=start_times[j];
   	if(end_times[j]>end)
    		end=end_times[j];
}
 flops_total_time=((double)(end-start))/1000000.0;
 printf("\n\nTotal time taken by %d threads for FLOPS is:%ld microseconds and %lf seconds",NUM_THREADS,(end-start),flops_total_time);
   
  
   for(t=0; t<NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads_iops[t], NULL, ComputeIops, (void *)t);
   }
    //wait for all child threads to finish
    for(t=0; t<NUM_THREADS; t++){
	pthread_join(threads_iops[t],NULL);
    }
  //get the starting and largest time
  
  start_iop=start_times_iop[0];
//printf("start_iop:%ld",start_iop);

  end_iop=end_times_iop[0];
//printf("end_iop:%ld",end_iop);
  for(j=1;j<NUM_THREADS;j++)
  {
        if(start_times_iop[j]< start_iop)
   		start_iop=start_times_iop[j];
   	if(end_times_iop[j]>end_iop)
    		end_iop=end_times_iop[j]; 
  } 
  printf("The starting time is:%ld",start);  
  printf("The starting ending time is:%ld",end);
 
  iops_total_time=((double)(end_iop-start_iop))/1000000.0;
  
  printf("\n\n Total time taken by %d threads for IOPS is:%ld microseconds and %lf seconds",NUM_THREADS,(end_iop-start_iop),iops_total_time);
  
  printf("\nprinting GIGA FLOPS...\n");
  printf("%lf",((double)(10000000000.0))/(flops_total_time*1000000000.0));
  printf("\n****\n"); 
  printf("printing GIGA IOPS\n");
  printf("%lf",((double)(10000000000.0))/(iops_total_time*1000000000.0));
  /* Last thing that main() should do */
  pthread_exit(NULL);
}
