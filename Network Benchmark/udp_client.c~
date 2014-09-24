#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_CLIENTS 32
#define NUM_BLOCKS 10000000
#define BLOCK_SIZE 65507
long start_times[NUM_CLIENTS];
long end_times[NUM_CLIENTS];
void *connection_handler(void *);
int main(int argc, char *argv[]) {

    struct hostent *host;
    pthread_t thread[NUM_CLIENTS];
    long i, j,start,end;
    int n;
    double time_s;
    if (argc != 2) {
	printf("\n Usage: %s <ip of server> \n",argv[0]);
	return 1;
    }

    host = gethostbyname(argv[1]);
    if (host == NULL) {
	perror("gethostbyname");
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
    int sockfd = 0,i,s,n = 0;
    struct sockaddr_in server;
    char message[BLOCK_SIZE];
    int len = sizeof(struct sockaddr_in);
    struct timeval start,stop;
    /* initialize socket */
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
	perror("socket");
	return;
    }

    /* initialize server addr */
    memset((char *) &server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);

    /* send message */
    for(i=0;i<BLOCK_SIZE;i++)
    {
    message[i]='a';
    }
    printf("Client processing:%ld\n", threadnum);

    gettimeofday(&start,NULL);
    start_times[threadnum]=(start.tv_sec*1000000)+start.tv_usec;
    for(i=0;i<NUM_BLOCKS/NUM_CLIENTS;i++)
    { 
    if (sendto(s, message, BLOCK_SIZE, 0, (struct sockaddr *) &server, len) == -1) {
	perror("sendto()");
	return;
    }
    } 
    gettimeofday(&stop,NULL);
    end_times[threadnum]=(stop.tv_sec*1000000)+stop.tv_usec;
    printf("\n start time : %ld stop time is:%ld\n",(start.tv_sec*1000000)+start.tv_usec,(stop.tv_sec*1000000)+stop.tv_usec);
   
    close(s);
    return 0;
}
