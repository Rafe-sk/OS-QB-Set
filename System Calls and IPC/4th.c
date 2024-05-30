// write a C program to illustrate the concept of signal system call.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("Caught signal %d\n", signum);
}

int main() {
    signal(SIGINT, handler);
    while (1) {
        printf("Running...\n");
        sleep(1);
    }
    return 0;
}
