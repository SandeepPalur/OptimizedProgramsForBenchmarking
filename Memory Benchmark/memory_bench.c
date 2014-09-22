#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<pthread.h>
#include <string.h>
#define NUM_THREADS 1
#define NUM_BLOCKS  20971520
int thrdcount=0,k=0;
int choice;
pthread_t thread1,thread2;
clock_t startTime,endTime;

void* dummy_byte(void *);
void* dummy_kb(void *);
void* dummy_mb(void *);
void* rand_byte(void *);
void* rand_kb(void *);
void* rand_mb(void *);

void main()
{
	double time;
	
	//while(1)
//	{
			printf("1.Sequential Access  2.Random Access 3.Exit\n");
			printf("Enter your choice\n");
			scanf("%d",&choice);
                        pthread_t threads[NUM_THREADS];
                        int rc;
                         long t;
			switch(choice)
			{

			case 1:
			
				startTime=clock();
                               for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, dummy_byte, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                               }
        		        for(t=0;t<NUM_THREADS;t++){
        			pthread_join(threads[t],NULL);
                                }		
				endTime=clock();			
                          time=(double)(endTime-startTime)/CLOCKS_PER_SEC;
			printf("The time for 1B block size is %lf \n",time);
printf("Throughput for 1B block size in sequential read is %lf MB/sec\n ",((double)NUM_BLOCKS/(time*1024*1024)));
				
                               startTime=clock();
				for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, dummy_kb, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                               }
        		        for(t=0;t<NUM_THREADS;t++){
        			pthread_join(threads[t],NULL);
                                }
                                endTime=clock();
			          time=(double)(endTime-startTime)/CLOCKS_PER_SEC;
			printf("The time for 1B block size is %lf \n",time);
	  printf("Throughput for 1KB block size in sequential read is %f MB/sec\n",(((double)NUM_BLOCKS*1024)/(time*1024*1024)));
				
			startTime=clock();
				for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, dummy_mb, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                               }
        		        for(t=0;t<NUM_THREADS;t++){
        			pthread_join(threads[t],NULL);
                                }
                                endTime=clock();
				
      time=(double)(endTime-startTime)/CLOCKS_PER_SEC;
			printf("The time for 1B block size is %lf \n",time);
	  printf("Throughput for 1MB block size in sequential read is %f MB/sec\n",(((double)NUM_BLOCKS*1024*1024)/(time*1024*1024)));
break;                	




			case 2:
			
				
				startTime=clock();
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
	 		endTime=clock();
						
			 time=(double)(endTime-startTime)/CLOCKS_PER_SEC;
			printf("The time for 1B block size is %lf \n",time);
	  printf("Throughput for 1KB block size in random read is %f MB/sec\n",(((double)NUM_BLOCKS)/(time*1024)));
				

				
				startTime=clock();
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
				endTime=clock();
				
            time=(double)(endTime-startTime)/CLOCKS_PER_SEC;
			printf("The time for 1B block size is %lf \n",time);
	  printf("Throughput for 1KB block size in random read is %f MB/sec\n",(((double)NUM_BLOCKS)/(time*1024)));

				
                               
				
				startTime=clock();
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

				endTime=clock();
				
				
				time=(double)(endTime-startTime)/CLOCKS_PER_SEC;
			printf("The time for 1B block size is %lf \n",time);
	  printf("Throughput for 1MB block size in random read is %f MB/sec\n",(((double)NUM_BLOCKS)/(time)));
break;

				
                                default : exit(0);
			        break;
        }
    }
//}

void* dummy_byte(void* param)
{


        long long i;
        int j;
        char *array1, *array2, *temp;
        array1 = (char *)malloc((NUM_BLOCKS/NUM_THREADS));
        array2 = 	(char *)malloc(NUM_BLOCKS/NUM_THREADS);
        memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
                for(i=0;i<NUM_BLOCKS/NUM_THREADS;i++)
                {
                        memcpy(array2+(i),array1+(i),1);
                }
	
}


void* dummy_kb(void* param)
{
        long long i;
        int j;
        char *array1, *array2, *temp;
        array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
        
                for(i=0;i<((NUM_BLOCKS/1024)-1)/NUM_THREADS;i++)
                {
                        memcpy(array2+(i*1024),array1+(i*1024),1024);
                }
      
}


void* dummy_mb(void* param)
{
        long long i;
        int j;
        char *array1, *array2, *temp1;
        array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
                for(i=0;i<((NUM_BLOCKS/(1024*1024))-1)/NUM_THREADS;i++)
                {
                        memcpy(array2+(i*1024*1024),array1+(i*1024*1024),1048576);
                }
        
}

void* rand_byte(void* param)
{    

  long long i;
        int j;
        char *array1, *array2, *temp;
        array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
                for(i=0;i<NUM_BLOCKS/NUM_THREADS;i++)
                {
                         k=rand()%1048576;
			memcpy(array2+i,array1+k,1);
                }

    		
		
	
}

void* rand_kb(void* param)
{
       long long i;
        int j;
        char *array1, *array2, *temp;
        array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
        
                for(i=0;i<((NUM_BLOCKS/1024)-1)/NUM_THREADS;i++)
                {
                        k=rand()%20479;
                        memcpy(array2+(i*1024),array1+(k*1024),1024);
                }       
       
}


void* rand_mb(void* param)
{

      long long i;
        int j;
        char *array1, *array2, *temp1;
        array1 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        array2 = (char *)malloc(NUM_BLOCKS/NUM_THREADS);
        memset(array2,'a',NUM_BLOCKS/NUM_THREADS);
                for(i=0;i<((NUM_BLOCKS/(1024*1024))-1)/NUM_THREADS;i++)
                {
                        k=rand()%19;
			memcpy(array2+(i*1048576),array1+(k*1048576),1048576);
                }
                        
		
}
