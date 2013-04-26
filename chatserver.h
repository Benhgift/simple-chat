#ifndef CHATSERVER_H
#define CHATSERVER_H


//----- HTTP response messages ----------------------------------------------
#define OK_IMAGE    "HTTP/1.0 200 OK\nContent-Type:image/gif\n\n"
#define OK_TEXT     "HTTP/1.0 200 OK\nContent-Type:text/html\n\n"
#define NOTOK_404   "HTTP/1.0 404 Not Found\nContent-Type:text/html\n\n"
#define MESS_404    "<html><body><h1>FILE NOT FOUND</h1></body></html>"
 
//----- Defines -------------------------------------------------------------
#define PORT_NUM            6110     // Port number for a Web server (TCP 5080)
#define PEND_CONNECTIONS     100     // pending connections to hold 
#define TRUE                   1
#define FALSE                  0
#define NTHREADS 5                     /* Number of child threads        */ 
#define NUM_LOOPS  10                  /* Number of local loops          */
#define SCHED_INTVL 5                  /* thread scheduling interval     */
#define HIGHPRIORITY 10

void* client_thread(void *);

#endif
