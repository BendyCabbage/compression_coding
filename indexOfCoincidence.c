#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGE_LENGTH 1000
#define NUM_LETTERS 26

char to_lower(char c);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./main someMessageOrSomething\n");
        exit(EXIT_FAILURE);
    }

    int message_length = strlen(argv[1]);
    printf("Message length: %d\n", message_length);
    int frequencies[NUM_LETTERS] = { 0 };

    for (int i = 0; i < message_length; i++) {
        char current_char = to_lower(argv[1][i]);
        if (current_char <= 'z' && current_char >= 'a') {
            frequencies[current_char - 'a'] += 1;
        }
    }
    double numerator = -1 * message_length;
    double denominator = message_length * message_length - message_length;
    for (int i = 0; i < NUM_LETTERS; i++) {
        numerator += frequencies[i] * frequencies[i];
    }
    printf("Index of coincidence: %lf\n", numerator / denominator);
    printf("As a fraction: %d / %d\n", (int) numerator, (int) denominator);
    return 0;
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        c += 'a' - 'A';
    }
    return c;
}