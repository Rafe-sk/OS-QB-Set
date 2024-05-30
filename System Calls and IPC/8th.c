// write a C program to demonstrate IPC using semaphores.

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key = ftok("semfile", 65);
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    struct sembuf sb = {0, -1, 0}; // Lock
    semop(semid, &sb, 1);
    printf("Critical section start\n");
    sleep(2);
    printf("Critical section end\n");
    sb.sem_op = 1; // Unlock
    semop(semid, &sb, 1);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
