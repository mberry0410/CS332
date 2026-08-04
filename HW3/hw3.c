/* Homework 3
Name: Madison Byrd
BlazerID: mjbyrd
To Compile: make 
To run: ./hw3 <directory_name>
        ./hw3 .
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>

// Helper to check if the file has a specific extension
int has_extension(const char *filename, const char *ext) {
    size_t len = strlen(filename);
    size_t ext_len = strlen(ext);
    if (len < ext_len) return 0;
    return strcmp(filename + len - ext_len, ext) == 0;
}

// Counts words in a file 
long count_words(const char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        return -1;
    }

    long words = 0;
    int in_word = 0;
    int c;

    while ((c = fgetc(fp)) != EOF) {
        if (isspace(c)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    fclose(fp);
    return words;
}

// Gets info for one file and print output
int process_file(const char *filepath, const char *filename) {
    struct stat st;

    // Get file info
    if (stat(filepath, &st) != 0) {
        fprintf(stderr, "Error: Unable to stat file '%s': %s\n", filepath, strerror(errno));
        return EXIT_FAILURE;
    }

    // Only counts words if it's a .txt file
    long words = -1;
    if (has_extension(filename, ".txt")) {
        words = count_words(filepath);
        if (words < 0) {
            fprintf(stderr, "Error: Failed to open file '%s' for word count: %s\n", filepath, strerror(errno));
            return EXIT_FAILURE;
        }
    }

    // Prints output
    if (words >= 0) {
        printf("File: %s | Size: %ld bytes | Words: %ld\n", 
               filename, (long)st.st_size, words);
    } else {
        printf("File: %s | Size: %ld bytes\n", 
               filename, (long)st.st_size);
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    // Makes sure exactly one command-line argument is passed
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *dir_path = argv[1];

    // Opens directory
    DIR *dir = opendir(dir_path);
    if (!dir) {
        fprintf(stderr, "Error: Directory not found or inaccessible: %s\n", dir_path);
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    // Loops through files in folder
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Builds full file path
        char filepath[PATH_MAX];
        snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, entry->d_name);

        // Checks file type
        struct stat entry_stat;
        if (stat(filepath, &entry_stat) != 0) {
            fprintf(stderr, "Error: Cannot inspect '%s': %s\n", filepath, strerror(errno));
            continue;
        }

        // Only processes regular files 
        if (S_ISREG(entry_stat.st_mode)) {
            printf("DEBUG: %s\n", entry->d_name);

            char filename[NAME_MAX + 1];
            strcpy(filename, entry->d_name);
            pid_t pid = fork();

            if (pid < 0) {
                fprintf(stderr, "Error: Failed to create child process for '%s': %s\n", 
                        entry->d_name, strerror(errno));
                closedir(dir);
                
                // Waits for existing children before exiting
                while (wait(NULL) > 0);
                exit(EXIT_FAILURE);
            } 
            else if (pid == 0) {
                // the child process
                closedir(dir);
                int status = process_file(filepath, filename);
                exit(status);
            }
        }
    }

    closedir(dir);

    // Parent waits for all child processes to finish
    while (wait(NULL) > 0);

    return 0;
}