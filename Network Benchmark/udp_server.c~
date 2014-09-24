#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_CLIENTS 32
#define NUM_BLOCKS 10000000
#define BLOCK_SIZE 65507    //for UDP (65535-(20+8))
void *connection_handler(void *);
int main(int argc, char* argv[]) {
  
    struct sockaddr_in self, other;
   
    int n,s;
    long t;
    int res,c,client_sock,connfd = 0;

    /* initialize socket */
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
	perror("socket");
	return 1;
    }

    /* bind to server port */
    //port = atoi(argv[1]);
    memset((char *) &self, 0, sizeof(struct sockaddr_in));
    self.sin_family = AF_INET;
    self.sin_port = htons(5000);
    self.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *) &self, sizeof(self)) == -1) {
	perror("bind");
	return 1;
    }
    pthread_t thread_id[NUM_CLIENTS];
    for(t=0;t<NUM_CLIENTS;t++)
    {
	puts("Client Connection accepted");
      if(res=pthread_create( &thread_id[t],NULL,connection_handler,(void *)&s)==0)
{
       printf("\n thread created");
}
	    else
{       
        printf("\nthread[%ld] creation failed",t);
}
	puts("Handler assigned");
    }
       //wait for all child threads to finish
   for(t=0; t<NUM_CLIENTS; t++){
	pthread_join(thread_id[t],NULL);
    }
//pthread_exit(NULL);
	return 0;
	}

void *connection_handler(void *socket_desc)
{
 
struct sockaddr_in other;
 int len = sizeof(struct sockaddr_in);
 char buf[BLOCK_SIZE];
int connfd = *(int*)socket_desc;
 int n;
    memset(buf, '0',sizeof(buf));
while(1){    

n = recvfrom(connfd, buf, BLOCK_SIZE, 0, (struct sockaddr *) &other, &len);
        fflush(stdout);
        //puts(buf);
        //puts("\n");
}
    close(connfd);
    return 0;
}
