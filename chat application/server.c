#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <bits/pthreadtypes.h>

#define MAX_SIZE 64
#define USERNAME_MIN 3
#define USERNAME_MAX 16
#define PORT 3131
#define BUFFER_SIZE 256

typedef struct {
    char username[USERNAME_MAX + 1];
    int conn_fd;
    int user_id;
} Client;

Client *active_clients[MAX_SIZE] = {NULL};
pthread_rwlock_t client_rwlock = PTHREAD_RWLOCK_INITIALIZER;

pthread_t *thread_pool = NULL;
int threadpool_size = MAX_SIZE;

void *client_handler(void *arg);
void broadcast_message(const char *message, int sender_id);
int is_valid_username(const char *username);

void cleanup_client(int user_id) {
    pthread_rwlock_wrlock(&client_rwlock);
    if (active_clients[user_id]) {
        close(active_clients[user_id]->conn_fd);
        free(active_clients[user_id]);
        active_clients[user_id] = NULL;
    }
    pthread_rwlock_unlock(&client_rwlock);
}

void *client_handler(void *arg) {
    int conn_fd = *(int *)arg;
    free(arg);

    char buffer[BUFFER_SIZE];
    char username[USERNAME_MAX + 1];
    int user_id = -1;

    // Prompt for username
    while (1) {
        send(conn_fd, "Enter username: ", 17, 0);
        memset(username, 0, sizeof(username));
        recv(conn_fd, username, sizeof(username) - 1, 0);

        if (!is_valid_username(username)) {
            send(conn_fd, "Invalid username. Must be 3-16 characters, only letters, numbers, and _.\n", 73, 0);
            continue;
        }

        pthread_rwlock_rdlock(&client_rwlock);
        int exists = 0;
        for (int i = 0; i < MAX_SIZE; i++) {
            if (active_clients[i] && strcmp(active_clients[i]->username, username) == 0) {
                exists = 1;
                break;
            }
        }
        pthread_rwlock_unlock(&client_rwlock);

        if (exists) send(conn_fd, "Username already exists. Try again.\n", 37, 0);
        else break;
    }

    // Add client to active_clients
    pthread_rwlock_wrlock(&client_rwlock);
    for (int i = 0; i < MAX_SIZE; i++) {
        if (!active_clients[i]) {
            active_clients[i] = malloc(sizeof(Client));
            strncpy(active_clients[i]->username, username, USERNAME_MAX+1);
            active_clients[i]->conn_fd = conn_fd;
            active_clients[i]->user_id = i;
            user_id = i;
            break;
        }
    }
    pthread_rwlock_unlock(&client_rwlock);

    if (user_id == -1) {
        send(conn_fd, "Server is full. Disconnecting.\n", 31, 0);
        close(conn_fd);
        return NULL;
    }

    snprintf(buffer, sizeof(buffer), "Welcome %s!\n", username);
    send(conn_fd, buffer, strlen(buffer), 0);

    // Main communication loop
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(conn_fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received <= 0) {
            break;
        }

        if (strncmp(buffer, "MSG", 3) == 0) {
            broadcast_message(buffer + 4, user_id);
        } 
        else {
            send(conn_fd, "Invalid command. Use MSG <message>.\n", 36, 0);
        }
    }

    cleanup_client(user_id);
    return NULL;
}

void broadcast_message(const char *message, int sender_id) {
    pthread_rwlock_rdlock(&client_rwlock);
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%s: %s\n", active_clients[sender_id]->username, message);

    for (int i = 0; i < MAX_SIZE; i++) {
        if (active_clients[i] /* && i != sender_id */) {
            send(active_clients[i]->conn_fd, buffer, strlen(buffer), 0);
        }
    }
    pthread_rwlock_unlock(&client_rwlock);
}

int is_valid_username(const char *username) {
    size_t len = strlen(username);
    printf("Raw username: '%s'\n", username);
    if (len < USERNAME_MIN || len > USERNAME_MAX) { // max check might be unnecessary
        return 0;
    }
    for (size_t i = 0; i < len; i++) {
        if (!isalnum(username[i]) && username[i] != '_') {
            return 0;
        }
    }
    return 1;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_SIZE) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int *conn_fd = malloc(sizeof(int));
        *conn_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

        if (*conn_fd < 0) {
            perror("Accept failed");
            free(conn_fd);
            continue;
        }

        printf("Client connected %d\n", *conn_fd);

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, client_handler, conn_fd);
        pthread_detach(client_thread);
    }

    close(server_fd);
    return 0;
}
