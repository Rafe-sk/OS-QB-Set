// write a C program to demonstrate inter-process communication (IPC) using pipes

#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if (pid == 0) {
        close(fd[0]);
        write(fd[1], "Hello from child", 16);
        close(fd[1]);
    } else {
        char buffer[20];
        close(fd[1]);
        read(fd[0], buffer, 16);
        printf("%s\n", buffer);
        close(fd[0]);
    }
    return 0;
}
