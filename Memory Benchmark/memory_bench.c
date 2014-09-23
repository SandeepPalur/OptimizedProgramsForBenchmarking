#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<pthread.h>
#include<string.h>
#define NUM_THREADS 1
#define NUM_BLOCKS 209715200

int choice;
long start_time[NUM_THREADS];
long end_time[NUM_THREADS];

void* seq_byte(void *);
void* seq_kb(void *);
void* seq_mb(void *);
void* rand_byte(void *);
void* rand_kb(void *);
void* rand_mb(void *);
void calculateTime(int num_bytes)
{
     double time_sec,time_computed;
     long start,end,i;
     start=start_time[0];
     end=end_time[0];
     for(i=0;i<NUM_THREADS;i++)
{
       if(start_time[i]<start)
       start=start_time[i];
       if(end_time[i]>end)
       end=end_time[i];
}
    time_sec=(double)(end-start)/1000000.0;
   
     printf("The time taken by %d threads for %d bytes is %lf seconds \n",NUM_THREADS,num_bytes,time_sec);
printf("Throughput for %d bytes block size by %d threads is %lf MB/sec\n ",num_bytes,NUM_THREADS,(double)(NUM_BLOCKS)/(time_sec*1024*1024));
 
}
void main()
{
			double time;
	                
			printf("1.Sequential Access  2.Random Access 3.Exit\n");
			printf("Enter your choice\n");
			scanf("%d",&choice);
                        pthread_t threads[NUM_THREADS];
                        int rc;
                        long t;
			switch(choice)
			{

			case 1:
			
			        for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, seq_byte, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                               }
        		        for(t=0;t<NUM_THREADS;t++){
        			pthread_join(threads[t],NULL);
                                }
                             calculateTime(1);		
				
                             
				for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, seq_kb, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                               }
        		        for(t=0;t<NUM_THREADS;t++){
        			pthread_join(threads[t],NULL);
                                }
                               calculateTime(1024);
		

				for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, seq_mb, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                               }
        		        for(t=0;t<NUM_THREADS;t++){
        			pthread_join(threads[t],NULL);
                                }
                                calculateTime(1048576);  //1024*1024
				break;
    
			case 2:
			
				for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, rand_byte, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                               }
        		        for(t=0;t<NUM_THREADS;t++){
        			pthread_join(threads[t],NULL);
                                }
	
			        calculateTime(1);
                                
				for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, rand_kb, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                               }
        		        for(t=0;t<NUM_THREADS;t++){
        			pthread_join(threads[t],NULL);
                                }
				
				calculateTime(1024);
                                
				for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, rand_mb, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                               }
        		        for(t=0;t<NUM_THREADS;t++){
        			pthread_join(threads[t],NULL);
                                }

				calculateTime(1048576);
				break;  

                                default : exit(0);
			        break;
        }
    }

void *seq_byte(void* param)
{
        
        struct timeval start,stop;
        long long i;
        long tid=(long)param;
        int j;
        
        char *array1, *array2, *temp;
        array1 = (char *)malloc((NUM_BLOCKS/NUM_THREADS));
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
	memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
	gettimeofday(&start,NULL);
        
                for(i=0;i<(NUM_BLOCKS/NUM_THREADS);i++)
                {
                        memcpy(array1+(i),array2+(i),1);
                }
        gettimeofday(&stop,NULL);
	start_time[tid]=(start.tv_sec*1000000)+start.tv_usec;
        end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
	
} 

void* seq_kb(void* param)
{
	struct timeval start,stop;
        long long i;
	long tid=(long)param;
        int j;
        char *array1, *array2, *temp;
	array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        
	memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
        gettimeofday(&start,NULL);
                for(i=0;i<(NUM_BLOCKS/(1024*NUM_THREADS));i++)
                {
                        memcpy(array1+(i*1024),array2+(i*1024),1024);
                }
          gettimeofday(&stop,NULL);
	 start_time[tid]=(start.tv_sec*1000000)+start.tv_usec;
        end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
}


void* seq_mb(void* param)
{
	struct timeval start,stop;
        long long i;
	long tid=(long)param;
        int j;
        char *array1, *array2, *temp1;
	array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
	
        memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
	gettimeofday(&start,NULL);
        start_time[tid]=(start.tv_sec*1000000)+start.tv_usec;
                for(i=0;i<(NUM_BLOCKS/(1024*1024*NUM_THREADS));i++)
                {
                        memcpy(array1+(i*1024*1024),array2+(i*1024*1024),1048576);
                }
	 gettimeofday(&stop,NULL);
        end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
        
}

void* rand_byte(void* param)
{    
	struct timeval start,stop;
  	long long i,k;
	long tid=(long)param;
        char *array1, *array2, *temp;
        long long M=0,N=(NUM_BLOCKS/NUM_THREADS);
        array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);

        memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
	gettimeofday(&start,NULL);
        start_time[tid]=(start.tv_sec*1000000)+start.tv_usec;
                for(i=0;i<(NUM_BLOCKS/NUM_THREADS);i++)
                {
                         //k=rand()%1048576;
			 srand((unsigned)time(NULL));
 			 k = M+rand() / (RAND_MAX/(N-M+1)+1);
			memcpy(array1+k,array2+k,1);
                }

    	 gettimeofday(&stop,NULL);
        end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;	
	
	
}

void* rand_kb(void* param)
{
	struct timeval start,stop;
        long long i,k;
	long tid=(long)param;
	long long M=0,N=(NUM_BLOCKS/(1024*NUM_THREADS));
        char *array1, *array2, *temp;
        array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
     
 	memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
	gettimeofday(&start,NULL);
        start_time[tid]=(start.tv_sec*1000000)+start.tv_usec;
                for(i=0;i<(NUM_BLOCKS/(1024*NUM_THREADS));i++)
                {
                        //k=rand()%20479;
			srand((unsigned)time(NULL));
                        k = M+rand() / (RAND_MAX/(N-M+1)+1);
                        memcpy(array1+(k),array2+(k*1024),1024);
                }       
        gettimeofday(&stop,NULL);
        end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;
       	
}


void* rand_mb(void* param)
{
	struct timeval start,stop;
        long long i,k;
	long tid=(long)param;        
	long long M=0,N=NUM_BLOCKS/(1024*1024*NUM_THREADS);
        char *array1, *array2, *temp1;
        array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
   
	memset(array2,'a',(NUM_BLOCKS/NUM_THREADS));
	gettimeofday(&start,NULL);
        start_time[tid]=(start.tv_sec*1000000)+start.tv_usec;
                for(i=0;i<(NUM_BLOCKS/(1024*1024*NUM_THREADS));i++)
                {
                        //k=rand()%19;
			srand((unsigned)time(NULL));
                        k = M+rand() / (RAND_MAX/(N-M+1)+1);
			memcpy(array1+(k),array2+(k*1048576),1048576);
                }
                        
	gettimeofday(&stop,NULL);
        end_time[tid]=(stop.tv_sec*1000000)+stop.tv_usec;	
	
}
