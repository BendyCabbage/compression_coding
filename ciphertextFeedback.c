#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char caesar_shift(char character, int shift);
char to_lower(char c);
int min(int i, int j);

void encrypt(int message_length, int key_length, char *message, char *key);
void decrypt(int message_length, int key_length, char *message, char *key);

int main (int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: ./vigenere key message (1 for encrypt, -1 for decrypt)");
        exit(EXIT_FAILURE);
    }
    char *key = argv[1];
    char *message = argv[2];
    int method = atoi(argv[3]);
    
    if (method != 1 && method != -1) {
        fprintf(stderr, "Last number must be 1 or -1\n");
        exit(EXIT_FAILURE);
    }

    int key_length = strlen(key);
    int message_length = strlen(message);

    if (method == 1) {
        encrypt(message_length, key_length, message, key);
    } else {
        decrypt(message_length, key_length, message, key);
    }
    return 0;
}

void encrypt(int message_length, int key_length, char *message, char *key) {
    //First few in shift amounts are the key
    int shift_amounts[message_length];
    for (int i = 0; i < key_length; i++) {
        shift_amounts[i] = to_lower(key[i]) - 'a';
    }

    char ciphertext[message_length + 1];

    int ciphertext_index = 0;
    while (ciphertext_index < message_length) {

        //Encrypt number of characters using key
        for (int i = ciphertext_index; i < min(key_length + ciphertext_index, message_length); i++) {
            ciphertext[i] = caesar_shift(message[i], shift_amounts[i]);
        }

        //Next ones in shift amounts are then those encrypted characters
        for (int i = ciphertext_index + key_length; i < min(message_length, 2 * key_length + ciphertext_index); i++) {
            shift_amounts[i] = to_lower(ciphertext[i - key_length]) - 'a';
        }
        ciphertext_index += key_length;
    }
    ciphertext[message_length] = '\0';
    printf("Ciphertext: %s\n", ciphertext);
}

void decrypt(int message_length, int key_length, char *message, char *key) {
    int shift_amounts[message_length];
    for (int i = 0; i < key_length; i++) {
        shift_amounts[i] = to_lower(key[i]) - 'a';
    }
    for (int i = key_length; i < message_length; i++) {
        shift_amounts[i] = to_lower(message[i - key_length]) - 'a';
    }
    char plaintext[message_length + 1];
    for (int i = 0; i < message_length; i++) {
        plaintext[i] = caesar_shift(message[i], -1 * shift_amounts[i]);
    }
    plaintext[message_length] = '\0';
    printf("Plaintext: %s\n", plaintext);
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

int min(int i, int j) {
    if (i <= j) return i;
    return j;
}