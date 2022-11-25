#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char caesar_shift(char character, int shift);
char to_lower(char c);
void print_array(int size, int array[size]);

int main (int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: ./vigenere key message (1 for encrypt -1 for decrypt)");
        exit(EXIT_FAILURE);
    }
    char *key = argv[1];
    char *message = argv[2];
    int method = atoi(argv[3]);
    
    if (method != 1 && method != -1) {
        fprintf(stderr, "Last number must be either 1 or -1\n");
        exit(EXIT_FAILURE);
    }

    int key_length = strlen(key);
    int message_length = strlen(message);

    int shift_amounts[message_length];
    for (int i = 0; i < message_length; i++) {
        shift_amounts[i] = to_lower(key[i % key_length]) - 'a';
    }

    char ciphertext[message_length];
    for (int i = 0; i < message_length; i++) {
        ciphertext[i] = caesar_shift(message[i], method * shift_amounts[i]);
    }
    if (method == 1) {
        printf("Ciphertext: ");
    } else {
        printf("Plaintext: ");
    }
    for (int i = 0; i < message_length; i++) {
        printf("%c", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

char caesar_shift(char character, int shift) {
    shift = shift % 26;
    if (shift < 0) {
        shift += 26;
    }
    if (character >= 'a' && character <= 'z') {
        character += shift - 'a';
        character = character % 26;
        character += 'a';
        return character;
    } else if (character >= 'A' && character <= 'Z') {
        character += shift - 'A';
        character = character % 26;
        character += 'A';
        return character;
    } else {
        return character;
    }
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        c += 'a' - 'A';
    }
    return c;
}