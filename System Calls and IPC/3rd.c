// write a C program to illustrate the concept of wait system call.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child process\n");
        _exit(0);
    } else if (pid > 0) {
        wait(NULL);
        printf("Child process terminated\n");
    } else {
        perror("fork");
        return 1;
    }
    return 0;
}
