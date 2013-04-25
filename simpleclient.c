#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
 
 
int main(int argc, char *argv[])
{
   printf("This is the client program\n");
 
   int sockfd;
   int len;
   struct sockaddr_in address;
   int result;
   char string[BUFFER_SIZE] = "joe";
 
   //Create socket for client.
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
   //Name the socket as agreed with server.
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = inet_addr("71.215.135.129");
   address.sin_port = htons(9999);
   len = sizeof(address);
 
   //
   result = connect(sockfd, (struct sockaddr *)&address, len);
 
   if(result == 1)
   {
      perror("Error has occurred");
      exit(0);
   }

 	
 	printf("Sending: %s\n", string);
   //Read and write via sockfd
   write(sockfd, &string, BUFFER_SIZE);
   read(sockfd, &string, BUFFER_SIZE);

   printf("String from server: %s\n", string);
   close(sockfd);
 
   exit(0);
}
