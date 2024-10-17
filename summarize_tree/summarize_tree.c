#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

// Global counters for directories and regular files
static int num_dirs, num_regular;

// Function to check if a given path is a directory
int is_dir(const char* path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return 0;
    }
    return S_ISDIR(statbuf.st_mode);
}

// Forward declaration of process_path function
void process_path(const char* path);

// Function to process a directory
void process_directory(const char* path) {
    DIR* dir = opendir(path);
    struct dirent* entry;
    if (dir == NULL) {
        return;
    }
    num_dirs++;  // Increment directory counter
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char new_path[1024];
                snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
                process_directory(new_path);
            }
        } else {
            num_regular++;  // Increment regular file counter
        }
    }
    closedir(dir);  // Close the directory
}

// Function to process a regular file
void process_file(const char* path) {
    num_regular++;  // Increment regular file counter
}

// Function to process a given path (either directory or file)
void process_path(const char* path) {
    if (is_dir(path)) {
        process_directory(path);  // If it's a directory, process it
    } else {
        process_file(path);  // If it's a regular file, process it
    }
}

int main (int argc, char *argv[]) {
    // Ensure an argument was provided.
    if (argc != 2) {
        printf ("Usage: %s <path>\n", argv[0]);
        printf ("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    num_dirs = 0;
    num_regular = 0;

    process_path(argv[1]);

    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
