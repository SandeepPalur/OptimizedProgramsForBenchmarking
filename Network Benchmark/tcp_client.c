#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <sys/time.h>
#include <pthread.h>
#define NUM_CLIENTS 64
#define NUM_BLOCKS 10000000
#define BLOCK_SIZE 1
long start_times[NUM_CLIENTS];
long end_times[NUM_CLIENTS];
void *connection_handler(void *);
int main(int argc, char *argv[])
{
    long i,j,start,end; 
    double time_s;
    pthread_t thread[NUM_CLIENTS];
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 
    for(i=0;i<NUM_CLIENTS;i++)
    {
     printf("In main: creating thread %ld\n", i);
     if(pthread_create(&thread[i],NULL,connection_handler,(void*)i)<0)
    {
            perror("could not create thread");
            return 1;
    }
    puts("connection getting handled...\n");
    }
   
  //wait for all child threads to finish
    for(i=0; i<NUM_CLIENTS; i++){
	pthread_join(thread[i],NULL);
    }
  //get the starting and largest time
  start=start_times[0];
  end=end_times[0];
  for(j=1;j<NUM_CLIENTS;j++)
  {
  	if(start_times[j]< start)
   		start=start_times[j];
   	if(end_times[j]>end)
    		end=end_times[j];
  } 
  printf("The starting time is:%ld",start);  
  printf("The starting ending time is:%ld",end);
  time_s=((double)(end-start))/1000000.0;
  printf("\n\nTotal Taken taken by %d clients is:%ld microseconds and %lf seconds\n",NUM_CLIENTS,end-start,time_s);
  printf("Throughput is %lf Megabits per second",(((double)NUM_BLOCKS*(double)BLOCK_SIZE)/(1024*1024*time_s))*8);  
 
  pthread_exit(NULL);
  return 0;
}


void *connection_handler(void *threadid)
{
    long threadnum=(long)threadid;
    int sockfd = 0,i,n = 0;
    struct timeval start,stop;
    char recvBuff[BLOCK_SIZE];
    struct sockaddr_in serv_addr;
    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return;
    } 

     bzero((char *) &serv_addr, sizeof (serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 

     
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return;
    } 
    printf("Connected successfully client:%ld\n", threadnum);
   
    gettimeofday(&start,NULL);
    start_times[threadnum]=(start.tv_sec*1000000)+start.tv_usec;
    for(i=0;i<NUM_BLOCKS/NUM_CLIENTS;i++)
    {
           n=read(sockfd,recvBuff,BLOCK_SIZE);
           //puts(recvBuff);
           //puts("\n");
    }
            
    if(n < 0)
    {
        printf("\n Read error \n");
    } 
    gettimeofday(&stop,NULL);
    end_times[threadnum]=(stop.tv_sec*1000000)+stop.tv_usec;
    printf("\n start time : %ld stop time is:%ld\n",(start.tv_sec*1000000)+start.tv_usec,(stop.tv_sec*1000000)+stop.tv_usec);
    //puts(recvBuff);
    close(sockfd);
    return 0;
}
