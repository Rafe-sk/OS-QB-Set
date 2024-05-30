// write a C program to demonstrate IPC using shared memory.

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);
    strcpy(str, "Hello, World");
    printf("Data written to shared memory: %s\n", str);
    shmdt(str);
    str = (char*) shmat(shmid, (void*)0, 0);
    printf("Data read from shared memory: %s\n", str);
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
