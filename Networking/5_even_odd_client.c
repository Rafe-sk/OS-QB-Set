#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0, num;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Enter a number: ");
    scanf("%d", &num);
    send(sock, &num, sizeof(int), 0);
    read(sock, buffer, 1024);
    printf("Server response: %s\n", buffer);
    close(sock);
    
    return 0;
}
