#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a character is a vowel
int is_vowel(char c) {
    // Array of vowel characters (both lowercase and uppercase)
    char vowels[] = "aeiouAEIOU";
    // Check if the character is in the vowels array
    return strchr(vowels, c) != NULL;
}

// Function to remove vowels from the input string and store the result in the output string
void disemvowel(char *input, char *output) {
    int j = 0; // Index for the output string
    // Iterate over each character in the input string
    for (int i = 0; input[i] != '\0'; i++) {
        // If the character is not a vowel, add it to the output string
        if (!is_vowel(input[i])) {
            output[j++] = input[i];
        }
    }
    // Null-terminate the output string
    output[j] = '\0';
}

int main(int argc, char *argv[]) {
    FILE *input_file = stdin; // Default input is standard input
    FILE *output_file = stdout; // Default output is standard output
    char *input_buffer; // Buffer to hold input data
    char *output_buffer; // Buffer to hold output data
    size_t buffer_size = 1024; // Size of the buffers

    // If an input file is specified as a command-line argument, open it
    if (argc > 1) {
        input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            perror("Error opening input file");
            return 1;
        }
    }

    // If an output file is specified as a command-line argument, open it
    if (argc > 2) {
        output_file = fopen(argv[2], "w");
        if (output_file == NULL) {
            perror("Error opening output file");
            return 1;
        }
    }

    // Allocate memory for the input and output buffers
    input_buffer = (char *)malloc(buffer_size);
    output_buffer = (char *)malloc(buffer_size);

    // Read lines from the input file, disemvowel them, and write to the output file
    while (fgets(input_buffer, buffer_size, input_file) != NULL) {
        disemvowel(input_buffer, output_buffer);
        fputs(output_buffer, output_file);
    }

    // Free the allocated memory for the buffers
    free(input_buffer);
    free(output_buffer);

    // Close the input file if it was opened from a file
    if (input_file != stdin) fclose(input_file);
    // Close the output file if it was opened from a file
    if (output_file != stdout) fclose(output_file);

    return 0;
}