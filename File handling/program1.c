#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define Num_bytes 10

int main() {
    int file;
    char buffer[Num_bytes + 1];
    ssize_t bytesRead;

    
    file = open("file.txt", O_RDONLY);
    if (file == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    
    bytesRead = read(file, buffer, Num_bytes);
    if (bytesRead < Num_bytes) {
        if (bytesRead == 0) {
            printf("End of file reached.\n");
        } else if (bytesRead == -1) {
            perror("Error reading file");
            close(file);
            return EXIT_FAILURE;
        }
    }


    buffer[bytesRead] = '\0';


    printf("First %d bytes: %s\n", Num_bytes, buffer);

    
    close(file);

    return EXIT_SUCCESS;
}