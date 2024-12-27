# Makefile for server.c
# make to compile the server.
# make run to compile and execute the server.
# make clean to remove the compiled files.
# make debug to compile with debugging information and run with gdb.

CC = gcc
CFLAGS = -Wall -Wextra -O2
DEBUG_FLAGS = -g
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

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)
	gdb ./$(TARGET)