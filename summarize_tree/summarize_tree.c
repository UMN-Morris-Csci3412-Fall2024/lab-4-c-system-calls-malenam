#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
    struct stat buf;
    if (stat(path, &buf) != 0) {
        perror("stat");
        return false;
    }
    return S_ISDIR(buf.st_mode);
}

void process_path(const char* path);

void process_directory(const char* path) {
    num_dirs++;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    chdir(path);
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            process_path(entry->d_name);
        }
    }
    chdir("..");
    closedir(dir);
}

void process_file(const char* path) {
    num_regular++;
}

void process_path(const char* path) {
    if (is_dir(path)) {
        process_directory(path);
    } else {
        process_file(path);
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
