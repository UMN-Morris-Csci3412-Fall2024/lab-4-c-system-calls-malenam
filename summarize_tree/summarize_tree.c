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
bool is_dir(const char* path) {
    struct stat buf;
    // Get file status
    if (stat(path, &buf) != 0) {
        perror("stat");
        return false;
    }
    // Check if the path is a directory
    return S_ISDIR(buf.st_mode);
}

// Forward declaration of process_path function
void process_path(const char* path);

// Function to process a directory
void process_directory(const char* path) {
    num_dirs++;  // Increment directory counter
    DIR *dir = opendir(path);  // Open the directory
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    chdir(path);  // Change to the directory
    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip the "." and ".." entries
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            process_path(entry->d_name);  // Process each entry
        }
    }
    chdir("..");  // Change back to the parent directory
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
        process_file(path);  // If it's a file, process it
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        printf("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    num_dirs = 0;
    num_regular = 0;

    process_path(argv[1]);

    printf("Processed all the files from %s.\n", argv[1]);
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
