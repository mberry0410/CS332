#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFFSIZE 4096

int main(int argc, char *argv[]) {
    int readFileDescriptor, writeFileDescriptor;
    long int n;
    char buf[BUFFSIZE];

    // Checks for the correct number of arguments 
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        exit(-1);
    }

    // Checks if both file names are the same
    if (strcmp(argv[1], argv[2]) == 0) {
        printf("Error: filenames cannot be the same.\n");
        exit(-1);
    }

    //Opens  file2 for reading 
    readFileDescriptor = open(argv[2], O_RDONLY);

    // Opens  file1 for writing 
    writeFileDescriptor = open(argv[1], O_WRONLY);

    if (readFileDescriptor == -1 || writeFileDescriptor == -1) {
        printf("Error opening file.\n");
        exit(-1);
    }

    // Moves to the end of file1 so we append instead of overwrite 
    if (lseek(writeFileDescriptor, 0, SEEK_END) == -1) {
        printf("Error using lseek.\n");
        exit(-1);
    }

    //Copies contents of file2 to the end of file1 
    while ((n = read(readFileDescriptor, buf, BUFFSIZE)) > 0) {
        if (write(writeFileDescriptor, buf, n) != n) {
            printf("Error writing to file.\n");
            exit(-1);
        }
    }

    if (n < 0) {
        printf("Error reading file.\n");
        exit(-1);
    }

    close(readFileDescriptor);
    close(writeFileDescriptor);

    return 0;
}

