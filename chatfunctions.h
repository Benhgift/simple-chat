#ifndef CHATFUNCTIONS_H
#define CHATFUNCTIONS_H

#define MAX_CLIENTS 20
#define MAX_MESS_BUF 1024

void add_client(int [], int);

void remove_client(int [], int);

int is_client(int [], int);

void print_clients(int []);

void send_to_all(int [], char []);

void send_message(int, char []);

int is_command(char []);

int parse_command(char []);

void do_command(int, int, int []);

#endif 

