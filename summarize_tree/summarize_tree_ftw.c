#include <stdio.h>
#include <sys/stat.h>
#include <ftw.h>

// Global counters for directories and regular files
static int num_dirs = 0;
static int num_regular = 0;

// Callback function for ftw
// fpath: path to the file
// sb: pointer to stat structure
// typeflag: type of the file (directory or regular file)
static int callback(const char *fpath, const struct stat *sb, int typeflag) {
    if (typeflag == FTW_D) {
        num_dirs++;  // Increment directory counter
    } else if (typeflag == FTW_F) {
        num_regular++;  // Increment regular file counter
    }
    return 0;  // Return 0 to tell ftw to continue
}

#define MAX_FTW_DEPTH 16  // Maximum depth for ftw to traverse


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        printf("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    ftw(argv[1], callback, MAX_FTW_DEPTH);

    printf("Processed all the files from %s.\n", argv[1]);
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}