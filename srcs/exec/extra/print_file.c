#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void print_file_content(int fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Read from the file descriptor and print to stdout
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_descriptor>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // int fd = atoi(argv[1]);
    if (fd <= 0) {
        fprintf(stderr, "Invalid file descriptor: %d\n", fd);
        exit(EXIT_FAILURE);
    }

    print_file_content(fd);
    // printf("File %s is received\n", );

    return 0;
}

