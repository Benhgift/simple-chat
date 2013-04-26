#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
 
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>        /* P-thread implementation        */    
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>

#define BUFFER_SIZE 1024
 
/* Child thread implementation ----------------------------------------- */
void* listen_for_server_strings(void * arg)
{

  unsigned int    sockfd;         //copy socket
  char string [BUFFER_SIZE+1];
  sockfd = *(unsigned int *)arg;        // copy the socket
  while (1) {
    printf("waiting...\n");
    /* receive the first HTTP request (HTTP GET) ------- */
    bzero(string, BUFFER_SIZE);
    read(sockfd, &string, BUFFER_SIZE);
    printf("String from server: %s\n", string);
  }
}
 
int main(int argc, char *argv[])
{
	printf("This is the client program\n");
 
	int sockfd;
  char client_text[1024];
	int len;
	struct sockaddr_in address;
	int result;
	char string[BUFFER_SIZE] = "joe";

  unsigned int          ids;                    // holds thread args
  pthread_t             threads;                // Thread ID (used by OS)
  pthread_attr_t        attr;                   //  pthread attributes
    pthread_attr_init(&attr);
 
	//Create socket for client.
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
	//Name the socket as agreed with server.
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(6110);
	len = sizeof(address);
 
	//
	result = connect(sockfd, (struct sockaddr *)&address, len);
  ids = sockfd;
  pthread_create (                        /* Create a child thread        */
             &threads,                    /* Thread ID (system assigned)  */    
             &attr,                       /* Default thread attributes    */
             listen_for_server_strings,   /* Thread routine               */
             &ids);                       /* Arguments to be passed       */

 
	if(result == 1)
	{
    perror("Error has occurred");
    exit(0);
	}

	
	//Read and write via sockfd
  while(1) {
    bzero(client_text, BUFFER_SIZE);
    scanf("Please enter text\n", &client_text);
    printf("Sending to server\n");
    write(sockfd, &client_text, BUFFER_SIZE);
  }
	close(sockfd);
	exit(0);
}
