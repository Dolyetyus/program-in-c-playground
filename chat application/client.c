#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define ADDRESS "127.0.0.1"
#define PORT 3131
#define BUFFER_SIZE 256

void *receive_messages(void *socket_fd) {
    int conn_fd = *(int *)socket_fd;
    char buffer[BUFFER_SIZE];
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(conn_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            printf("Disconnected from server.\n");
            exit(EXIT_FAILURE);
        }
        printf("%s", buffer);
    }
    return NULL;
}

int main() {
    int conn_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (conn_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ADDRESS, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(conn_fd);
        exit(EXIT_FAILURE);
    }

    if (connect(conn_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(conn_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    // Receive the initial prompt for username
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(conn_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        printf("Disconnected from server.\n");
        close(conn_fd);
        exit(EXIT_FAILURE);
    }
    printf("%s", buffer);

    // Send username
    char username[BUFFER_SIZE];
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';
    send(conn_fd, username, strlen(username), 0);

    // Create a thread to receive messages
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, &conn_fd);
    pthread_detach(recv_thread);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        char* res = fgets(buffer, BUFFER_SIZE, stdin);

        if (res[0]=='\0') res[0] = '\0'; // to handle the compiler warning

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }

        send(conn_fd, buffer, strlen(buffer), 0);
    }

    close(conn_fd);
    return 0;
}