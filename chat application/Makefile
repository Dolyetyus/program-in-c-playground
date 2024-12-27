# Makefile for server.c and client.c
# make to compile the server.
# make run to compile and execute the server.
# make clean to remove the compiled files.
# make debug to compile with debugging information and run with gdb.
# make connect to compile and execute the client.

CC = gcc
CFLAGS = -Wall -Wextra -O2
DEBUG_FLAGS = -g
SERVER_TARGET = server
CLIENT_TARGET = client

all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Server compilation
$(SERVER_TARGET): server.o
	$(CC) $(CFLAGS) -o $(SERVER_TARGET) server.o

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

# Client compilation
$(CLIENT_TARGET): client.o
	$(CC) $(CFLAGS) -o $(CLIENT_TARGET) client.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

run: $(SERVER_TARGET)
	./$(SERVER_TARGET)

clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET) server.o client.o

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(SERVER_TARGET)
	gdb ./$(SERVER_TARGET)

connect: $(CLIENT_TARGET)
	./$(CLIENT_TARGET)
