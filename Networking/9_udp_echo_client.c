#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    while (1) {
        printf("Enter message: ");
        fgets(buffer, 1024, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        int n = recvfrom(sockfd, buffer, 1024, 0, NULL, NULL);
        buffer[n] = '\0';
        printf("Server response: %s", buffer);
    }

    close(sockfd);
    return 0;
}
