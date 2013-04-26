#include "chatfunctions.h"
#include <stdio.h>
#include <string.h>

void add_client(int clients[], int new_client)
{
	// TODO make thread safe
	int i;
	int found = 0;

	if(!is_client(clients, new_client))
	{
		for(i = 0; i < MAX_CLIENTS; i++){
			if(clients[i] == 0){
				found = 1;
				break;
			}
		}

		if(found){
			clients[i] = new_client;
		}
		else{
			printf("Client tried to connect but no open spots");
		}
	}
}

void remove_client(int clients[], int old_client)
{
	int i;

	for(i = 0; i < MAX_CLIENTS; i++){
		if(clients[i] == old_client){
			clients[i] = 0;
			break;
		}
	}
}

int is_client(int clients[], int search)
{
	// TODO make thread safe
	int i;
	int found = 0;

	for(i = 0; i < MAX_CLIENTS; i++){
		if(clients[i] == search){
			found = 1;
			break;
		}
	}

	return found;
}

void print_clients(int clients[])
{
	int i;

	for(i = 0; i < MAX_CLIENTS; i++){
		if(clients[i] != 0){
			printf("Client id: %d\n", clients[i]);
		}
	}
}

void send_to_all(int clients[], char message[])
{
	int i;

	printf("Sending to all clients: %s\n", message);

	for (i = 0; i < MAX_CLIENTS; i++){
		if (clients[i] != 0){
			send_message(clients[i], message);
		}
	}
}

void send_message(int client_s, char message[])
{
	int stringlen;
	stringlen = strlen(message);

	printf("Sending to : %d\n", client_s);

	send(client_s, message, stringlen, 0);
}
