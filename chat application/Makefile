# Makefile for server.c
# make to compile the server.
# make run to compile and execute the server.
# make clean to remove the compiled files.

CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = server

all: $(TARGET)

$(TARGET): server.o
	$(CC) $(CFLAGS) -o $(TARGET) server.o

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) server.o