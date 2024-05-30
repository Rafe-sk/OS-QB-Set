#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
    fd_set readfds;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        
        int activity = select(sockfd + 1, &readfds, NULL, NULL, NULL);
        if (activity > 0) {
            int n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&cliaddr, &len);
            buffer[n] = '\0';
            sendto(sockfd, buffer, n, 0, (struct sockaddr *)&cliaddr, len);
        }
    }

    close(sockfd);
    return 0;
}
