#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include<sys/time.h>
#define NUM_BLOCKS 1
#define BLOCK_SIZE 1048576
#define NUM_THREADS 1

long start_times[NUM_THREADS];
long end_times[NUM_THREADS];

void computeTPT(){
int i;
double time_sec;
long least_begin_time=start_times[0];
long greatest_finish_time=end_times[NUM_THREADS-1];

for(i=0;i<NUM_THREADS;i++){
  if(least_begin_time>start_times[i])
    least_begin_time=start_times[i];
  if(greatest_finish_time<end_times[i])
    greatest_finish_time=end_times[i];
  }
  time_sec=(greatest_finish_time-least_begin_time)/1000000.0;
 printf("Time elapsed:%lf",time_sec );
 printf("Throughput:%lf MB/sec", (NUM_BLOCKS/(time_sec*1024*1024)*BLOCK_SIZE));
}

void *disk_seq_write(void *threadid)
{
     printf("seq write");
   struct timeval start,stop;
   FILE *fp;
   int i;
   long tid=(long)threadid;
   char buffer[BLOCK_SIZE+1];
   memset(buffer,'$',BLOCK_SIZE);
   /* Open file for both reading and writing */
   char filename[5]; 
   sprintf(filename, "%ld", tid);
   fp = fopen(filename, "w+");
   /* Write data to the file */
   gettimeofday(&start,NULL);
   start_times[tid]=start.tv_sec*1000000 + start.tv_usec;
   for(i=0;i < ((NUM_BLOCKS/BLOCK_SIZE)/NUM_THREADS);i++){
   fwrite(buffer, BLOCK_SIZE, 1, fp);
   }
   gettimeofday(&stop,NULL);
   end_times[tid]=stop.tv_sec*1000000 + stop.tv_usec;
   fclose(fp);
   
}

void *disk_rand_write(void *threadid)
{
    printf("random write");
   long tid=(long)threadid;
   struct timeval start,stop;
   FILE *fp;
   int i;
   char buffer[BLOCK_SIZE+1];
   memset(buffer,'$',BLOCK_SIZE); 
   char buffer1[BLOCK_SIZE+1];
   memset(buffer,'!',BLOCK_SIZE);
   /* Open file for both reading and writing */
   char filename[5]; 
   sprintf(filename, "%ld", tid);
   fp = fopen(filename, "w+");
   /* Write data to the file */
   for(i=0;i < ((NUM_BLOCKS/BLOCK_SIZE)/NUM_THREADS)+10;i++){
   fwrite(buffer, BLOCK_SIZE, 1, fp);
   } 
   gettimeofday(&start,NULL);
   start_times[tid]=start.tv_sec*1000000 + start.tv_usec;
   for(i=0;i < ((NUM_BLOCKS/BLOCK_SIZE)/NUM_THREADS);i++){
   fseek(fp, rand()%((NUM_BLOCKS/BLOCK_SIZE)/NUM_THREADS), SEEK_SET);
   fwrite(buffer1, BLOCK_SIZE,1, fp);
   }
   gettimeofday(&stop,NULL);
   end_times[tid]=stop.tv_sec*1000000 + stop.tv_usec;
   fclose(fp);
}

void *disk_seq_read(void *threadid)
{
     printf("seq read");
   struct timeval start,stop;
   long tid=(long)threadid;
   FILE *fp;
   int i;
   char buffer[BLOCK_SIZE+1];
   memset(buffer,'$',BLOCK_SIZE);
   /* Open file for both reading and writing */
   char filename[5]; 
   sprintf(filename, "%ld", tid);
   fp = fopen(filename, "w+");
   /* Write data to the file */
   for(i=0;i < ((NUM_BLOCKS/BLOCK_SIZE)/NUM_THREADS)+10;i++)
   fwrite(buffer, BLOCK_SIZE, 1, fp);
   fseek(fp,SEEK_SET,0);
   gettimeofday(&start,NULL);
   start_times[tid]=start.tv_sec*1000000 + start.tv_usec;
   for(i=0;i < ((NUM_BLOCKS/BLOCK_SIZE)/NUM_THREADS);i++){
   fread(buffer, BLOCK_SIZE, 1, fp);					
   }
   gettimeofday(&stop,NULL);
   end_times[tid]=stop.tv_sec*1000000 + stop.tv_usec;
   fclose(fp);

}

void *disk_rand_read(void *threadid)
{
     printf("random read");
   struct timeval start,stop;
   long tid=(long)threadid;
   FILE *fp;
   int i;
   char buffer[BLOCK_SIZE+1];
   memset(buffer,'$',BLOCK_SIZE);
   /* Open file for both reading and writing */
   char filename[5]; 
   sprintf(filename, "%ld", tid);
   fp = fopen(filename, "w+");
   /* Write data to the file */
   for(i=0;i < (((NUM_BLOCKS/BLOCK_SIZE)/NUM_THREADS)+10);i++)
   fwrite(buffer, BLOCK_SIZE, 1, fp);
   fseek(fp,SEEK_SET,0);
   gettimeofday(&start,NULL);
   start_times[tid]=start.tv_sec*1000000 + start.tv_usec;
   for(i=0;i < ((NUM_BLOCKS/BLOCK_SIZE)/NUM_THREADS);i++){
   fseek(fp, rand() % ((NUM_BLOCKS/BLOCK_SIZE)/NUM_THREADS), SEEK_SET);
   fread(buffer, BLOCK_SIZE, 1, fp);
   }
   gettimeofday(&stop,NULL);
   end_times[tid]=stop.tv_sec*1000000 + stop.tv_usec;
   fclose(fp);

}

main()
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   int user_option;
   long start,end;
   printf("1.sequential write	2.random write	3.sequential read   4.random read  5.exit"); 
   scanf("%d",&user_option);
   	switch(user_option){

   		case 1:
   			for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     			 	rc = pthread_create(&threads[t], NULL, disk_seq_write, (void *)t);
     			 	if (rc){
       			  		printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 		  		exit(-1);
        			}
                         }
        		for(t=0;t<NUM_THREADS;t++)
        			pthread_join(threads[t],NULL);
        		break;
   		case 2:
   			for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     				rc = pthread_create(&threads[t], NULL, disk_rand_write, (void *)t);
     				if (rc){
       					printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 				exit(-1);
        			}
   			}
        		for(t=0;t<NUM_THREADS;t++)
        			pthread_join(threads[t],NULL);
        		break;
                case 3:
			for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     				rc = pthread_create(&threads[t], NULL, disk_seq_read, (void *)t);
     				if (rc){
       					printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 				exit(-1);
        			}
   			}
        		for(t=0;t<NUM_THREADS;t++)
        			pthread_join(threads[t],NULL);
        		break;
                case 4:
			for(t=0;t<NUM_THREADS;t++){
     				printf("In main: creating thread %ld\n", t);
     				rc = pthread_create(&threads[t], NULL, disk_rand_read, (void *)t);
     				if (rc){
       					printf("ERROR; return code from pthread_create() is %d\n", rc);
      	 				exit(-1);
        			}
   			}
        		for(t=0;t<NUM_THREADS;t++)
        			pthread_join(threads[t],NULL);
        		break;
        
   		case 5:
        		exit(-1);
   		default:
        		printf("please enter a valid option");
        		break;     
     }	

   /* Last thing that main() should do */
   computeTPT();
   pthread_exit(NULL);
}


