#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_vowel(char c) {
    char vowels[] = "aeiouAEIOU";
    return strchr(vowels, c) != NULL;
}

void disemvowel(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (!is_vowel(input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

int main(int argc, char *argv[]) {
    FILE *input_file = stdin;
    FILE *output_file = stdout;
    char *input_buffer;
    char *output_buffer;
    size_t buffer_size = 1024;

    if (argc > 1) {
        input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            perror("Error opening input file");
            return 1;
        }
    }

    if (argc > 2) {
        output_file = fopen(argv[2], "w");
        if (output_file == NULL) {
            perror("Error opening output file");
            return 1;
        }
    }

    input_buffer = (char *)malloc(buffer_size);
    output_buffer = (char *)malloc(buffer_size);

    while (fgets(input_buffer, buffer_size, input_file) != NULL) {
        disemvowel(input_buffer, output_buffer);
        fputs(output_buffer, output_file);
    }

    free(input_buffer);
    free(output_buffer);

    if (input_file != stdin) fclose(input_file);
    if (output_file != stdout) fclose(output_file);

    return 0;
}