// write a C program to handle the SIGINT signal and print a message when it is received.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("SIGINT received\n");
}

int main() {
    signal(SIGINT, sigint_handler);
    printf("Press Ctrl+C to generate SIGINT\n");
    while (1) {
        sleep(1);
    }
    return 0;
}
