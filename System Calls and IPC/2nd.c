// write a C program to illustrate the concept of fork system call.

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("This is the child process\n");
    } else if (pid > 0) {
        printf("This is the parent process\n");
    } else {
        perror("fork");
        return 1;
    }
    return 0;
}
