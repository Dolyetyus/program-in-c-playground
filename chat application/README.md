# Client-Server Chat Application

This project consists of a simple client-server chat application implemented in C, because I'm bored and I wanted to work with networking in C. The client connects to the server, registers a username, and then can send and receive messages in real-time. The server handles multiple clients and manages their connections and messages.

## Features

- Client-side username registration with validation.
- Server-side client management with username validation.
- Real-time message exchange between connected clients.
- Graceful handling of client disconnections.

## Requirements

- C compiler (e.g., GCC)
- POSIX threads (`pthread`)
- Linux or UNIX-like operating system

## How to run?

- **make**: Compiles both the server and client code.
- **make run**: Compiles and runs the server.
- **make clean**: Removes the compiled binaries (`server`, `client`, and object files).
- **make debug**: Compiles the server with debugging information and starts it using `gdb` for debugging.
- **make connect**: Compiles and runs the client.

Thanks
