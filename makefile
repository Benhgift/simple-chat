CC=gcc
CFLAGS=-I. -lpthread
SERVER_DEPS = chatserver.h chatfunctions.h
CLIENT_DEPS = 

SERVER_OBJ = chatserver.o chatfunctions.o
CLIENT_OBJ = simpleclient.o

all: chatserver chatclient

%.o: %.c $(SERVER_DEPS)
	$(CC) -c -o $@ $< 

chatserver: $(SERVER_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

chatclient: $(CLIENT_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)