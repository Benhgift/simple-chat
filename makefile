CC=gcc
CFLAGS=-I. -lpthread
DEPS = chatserver.h chatfunctions.h
OBJ = chatserver.o chatfunctions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chatserver: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)