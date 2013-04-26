//----- Include files ---------------------------------------------------------
#include <stdio.h>          // for printf()
#include <stdlib.h>         // for exit()
#include <string.h>         // for strcpy(),strerror() and strlen()
#include <fcntl.h>          // for file i/o constants
#include <sys/stat.h>       // for file i/o constants
#include <errno.h>
 
/* FOR BSD UNIX/LINUX  ---------------------------------------------------- */
#include <sys/types.h>      //   
#include <netinet/in.h>     //   
#include <sys/socket.h>     // for socket system calls  
#include <arpa/inet.h>      // for socket system calls (bind) 
#include <sched.h>   
#include <pthread.h>        /* P-thread implementation        */    
#include <signal.h>         /* for signal                     */ 
#include <semaphore.h>      /* for p-thread semaphores        */
/* ------------------------------------------------------------------------ */ 
 

#include "chatfunctions.h"
#include "chatserver.h"
 
/* global variables ---------------------------------------------------- */
sem_t thread_sem[NTHREADS];  
int   next_thread;  
int   can_run;
int   i_stopped[NTHREADS]; 

unsigned int client_sock_list[MAX_CLIENTS] = {0};
 
unsigned int client_s;               // Client socket descriptor
 
 
/* Child thread implementation ----------------------------------------- */
void* client_thread(void * arg)
{
  unsigned int    myClient_s;         //copy socket
   
  /* other local variables ------------------------------------------------ */
  char           in_buf[MAX_MESS_BUF];           // Input buffer for GET resquest
  char           out_buf[MAX_MESS_BUF];          // Output buffer for HTML response
  char           *file_name;                 // File name
  unsigned int   fh;                         // File handle (file descriptor)
  unsigned int   buf_len;                    // Buffer length for file reads
  unsigned int   retcode;                    // Return code
 
  myClient_s = *(unsigned int *)arg;        // copy the socket

  add_client(client_sock_list, myClient_s);
  print_clients(client_sock_list);
 
  /* receive the first HTTP request (HTTP GET) ------- */
  retcode = recv(client_s, in_buf, MAX_MESS_BUF, 0);

  /* if receive error --- */
  if (retcode < 0)
  {   
    printf("recv error detected ...\n");
  }
 
  /* if HTTP command successfully received --- */
  else
  {    
    // Echo message to all clients
    send_to_all(client_sock_list, in_buf);

    remove_client(client_sock_list, client_s);
    pthread_exit(NULL);
  }
}

 
//===== Main program ========================================================
int main(void)
{
  /* local variables for socket connection -------------------------------- */
  unsigned int          server_s;               // Server socket descriptor
  struct sockaddr_in    server_addr;            // Server Internet address
  //unsigned int            client_s;           // Client socket descriptor
  struct sockaddr_in    client_addr;            // Client Internet address
  struct in_addr        client_ip_addr;         // Client IP address
  int                   addr_len;               // Internet address length
 
  unsigned int          ids;                    // holds thread args
  pthread_attr_t        attr;                   //  pthread attributes
  pthread_t             threads;                // Thread ID (used by OS)
 
  /* create a new socket -------------------------------------------------- */
  server_s = socket(AF_INET, SOCK_STREAM, 0);
 
  /* fill-in address information, and then bind it ------------------------ */
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT_NUM);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(server_s, (struct sockaddr *)&server_addr, sizeof(server_addr));
 
  /* Listen for connections and then accept ------------------------------- */
  listen(server_s, PEND_CONNECTIONS);
 
  /* the web server main loop ============================================= */
  pthread_attr_init(&attr);
  while(TRUE)
  {
    printf("Server is ready on port %d ...\n", PORT_NUM);
 
    /* wait for the next client to arrive -------------- */
    addr_len = sizeof(client_addr);
    client_s = accept(server_s, (struct sockaddr *)&client_addr, &addr_len);
 
    printf("a new client arrives ...\n");  
 
    if (client_s == FALSE)
    {
      printf("ERROR - Unable to create socket \n");
      exit(FALSE);
    }
 
    else
    {
      /* Create a child thread --------------------------------------- */
      ids = client_s;
      pthread_create (                    /* Create a child thread        */
                 &threads,                /* Thread ID (system assigned)  */    
                 &attr,                   /* Default thread attributes    */
                 client_thread,               /* Thread routine               */
                 &ids);                   /* Arguments to be passed       */
 
    }
  }
 
  /* To make sure this "main" returns an integer --- */
  close (server_s);  // close the primary socket
  return (TRUE);        // return code from "main"
}
