#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <arpa/inet.h>

#define PORT 8080

void send_file_list(int socket) {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                send(socket, dir->d_name, strlen(dir->d_name), 0);
                send(socket, "\n", 1, 0);
            }
        }
        closedir(d);
    }
    send(socket, "END", 3, 0);
}

void handle_client(int new_socket) {
    send_file_list(new_socket);

    char filename[1024] = {0};
    read(new_socket, filename, 1024);
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        char *error_msg = "File not found!";
        send(new_socket, error_msg, strlen(error_msg), 0);
        close(new_socket);
        return;
    }

    char buffer[1024];
    while (fgets(buffer, 1024, fp) != NULL) {
        send(new_socket, buffer, strlen(buffer), 0);
    }
    fclose(fp);
    close(new_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1, addrlen = sizeof(address);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}
