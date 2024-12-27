#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#define ADDRESS "127.0.0.1"
#define PORT 3132
#define BUFFER_SIZE 256

// Mutex for controlling terminal output
pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;

void clear_line() {
    printf("\33[2K\r"); // Clear the current line and move the cursor to the start
    fflush(stdout);
}

void display_prompt() {
    printf("You: ");
    fflush(stdout);
}

void *receive_messages(void *socket_fd) {
    int conn_fd = *(int *)socket_fd;
    char buffer[BUFFER_SIZE];
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(conn_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            pthread_mutex_lock(&output_mutex);
            clear_line();
            printf("Disconnected from server.\n");
            pthread_mutex_unlock(&output_mutex);
            exit(EXIT_FAILURE);
        }

        pthread_mutex_lock(&output_mutex);
        clear_line();
        printf("%s\n", buffer); // Display received message
        display_prompt();       // Restore prompt
        pthread_mutex_unlock(&output_mutex);
    }
    return NULL;
}

void register_username(int conn_fd) {
    char buffer[BUFFER_SIZE];
    char username[BUFFER_SIZE];
    int is_welcome_received = 0;

    while (!is_welcome_received) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(conn_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            printf("Disconnected from server.\n");
            close(conn_fd);
            exit(EXIT_FAILURE);
        }
        printf("%s", buffer);

        // Check if the server sent a "Welcome" message
        if (strncmp(buffer, "Welcome", 7) == 0) {
            is_welcome_received = 1;
            break;
        }

        fgets(username, BUFFER_SIZE, stdin);
        if (username[0] == '\0') continue;  // Skip if user presses enter right away
        username[strcspn(username, "\n")] = '\0';
        send(conn_fd, username, strlen(username), 0);
    }
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

    register_username(conn_fd);

    // Create a thread to receive messages
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, &conn_fd);
    pthread_detach(recv_thread);

    char buffer[BUFFER_SIZE];
    while (1) {
        pthread_mutex_lock(&output_mutex);
        display_prompt();
        pthread_mutex_unlock(&output_mutex);

        memset(buffer, 0, BUFFER_SIZE);
        char *res = fgets(buffer, BUFFER_SIZE, stdin);

        if (res == NULL || res[0] == '\0') continue; // Handle empty input

        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline

        if (strncmp(buffer, "exit", 4) == 0) {
            pthread_mutex_lock(&output_mutex);
            clear_line();
            printf("Exiting...\n");
            pthread_mutex_unlock(&output_mutex);
            break;
        }

        send(conn_fd, buffer, strlen(buffer), 0);
    }

    close(conn_fd);
    return 0;
}