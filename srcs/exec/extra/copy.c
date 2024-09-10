#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void copy_file_content(const char *source_file, const char *dest_file) {
    FILE *src = fopen(source_file, "rb");
    if (src == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    FILE *dest = fopen(dest_file, "wb");
    if (dest == NULL) {
        perror("Error creating destination file");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dest) != bytes_read) {
            perror("Error writing to destination file");
            fclose(src);
            fclose(dest);
            exit(EXIT_FAILURE);
        }
    }

    if (ferror(src)) {
        perror("Error reading from source file");
    }

    fclose(src);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_file = argv[1];
    const char *dest_file = "copied_file.txt";  // Change the destination file name as needed

    copy_file_content(source_file, dest_file);

    printf("File copied successfully to %s\n", dest_file);

    return EXIT_SUCCESS;
}