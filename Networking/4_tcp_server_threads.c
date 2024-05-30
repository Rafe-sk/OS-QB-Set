#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

void reverse_string(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void* handle_client(void* arg) {
    int client_fd = *(int*)arg;
    free(arg); // Free the allocated memory here
    char buffer[1024];

    read(client_fd, buffer, sizeof(buffer));
    reverse_string(buffer);
    write(client_fd, buffer, strlen(buffer));
    close(client_fd);
    return NULL;
}

int main() {
    int server_fd, *client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    pthread_t tid;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(1);
    }

    listen(server_fd, 5);

    while (1) {
        client_fd = malloc(sizeof(int));
        if (client_fd == NULL) {
            perror("malloc");
            continue;
        }

        *client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
        if (*client_fd < 0) {
            perror("accept");
            free(client_fd);
            continue;
        }

        if (pthread_create(&tid, NULL, handle_client, client_fd) != 0) {
            perror("pthread_create");
            free(client_fd);
            continue;
        }

        pthread_detach(tid); // Detach the thread to clean up resources automatically
    }

    close(server_fd);
    return 0;
}
