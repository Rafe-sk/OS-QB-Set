// write a C program to illustrate the concept of dup system call.
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = dup(STDOUT_FILENO);
    if (fd == -1) {
        perror("dup");
        return 1;
    }
    write(fd, "This is a dup test\n", 19);
    close(fd);
    return 0;
}
