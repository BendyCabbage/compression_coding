/*
Made by Josh Caithness (https://github.com/BendyCabbage)
Made for MATH3411 (Information, Codes and Ciphers)
Only use for educational purposes

Encodes and decodes using arithmetic coding
*/

#include <stdio.h>
#include <assert.h>

void encode(int num_symbols, long double probabilities[num_symbols + 2]);
void decode(int num_symbols, long double probabilities[num_symbols + 2]);

long double sum_to_index(
    int num_symbols, long double probabilities[num_symbols + 2], 
    int index
);
int find_interval(
    int num_symbols, long double probabilities[num_symbols + 2], 
    long double code_number
);

int main (void) {

    printf("How many symbols are there? ");
    int num_symbols;
    scanf("%d", &num_symbols);

    printf("Enter probabilities (p1 p2...): ");
    long double probabilities[num_symbols + 2];
    probabilities[0] = 0;
    for (int i = 1; i <= num_symbols; i++) {
        scanf("%Lf", &(probabilities[i]));
    }
    probabilities[num_symbols + 1] = 1;

    int is_encoding;
    printf("Type 1 to encode, 2 to decode: ");
    scanf("%d", &is_encoding);
    if (is_encoding == 1) {
        encode(num_symbols, probabilities);
    } else {
        decode(num_symbols, probabilities);
    }

}

void encode(int num_symbols, long double probabilities[num_symbols + 2]) {
    long double current_lower_bound = 0;
    long double current_bound_width = 1;

    int symbol_number;
    printf("Enter the number of the symbols separated by a space: ");
    while (scanf("%d", &symbol_number) != EOF) {
        assert(symbol_number <= num_symbols && symbol_number > 0);

        current_lower_bound += sum_to_index(num_symbols, probabilities, symbol_number) * current_bound_width;
        current_bound_width *= probabilities[symbol_number];

        if (symbol_number >= num_symbols) break;
    }

    printf("Lower bound: %Lf\n", current_lower_bound);
    printf("Upper bound: %Lf\n", current_bound_width + current_lower_bound);

}

void decode(int num_symbols, long double probabilities[num_symbols + 2]) {
    printf("Enter a number to decode: ");
    long double code_number;
    scanf("%Lf", &code_number);

    int current_symbol = 0;
    while (current_symbol < num_symbols) {
        current_symbol = find_interval(num_symbols, probabilities, code_number);
        printf("s%d\n", current_symbol);

        //Rescaling code number
        long double interval_lower_bound = sum_to_index(num_symbols, probabilities, current_symbol);
        long double interval_width = probabilities[current_symbol];

        code_number = (code_number - interval_lower_bound) / interval_width;
    }
}

//Finds the interval containing the given code number
int find_interval(int num_symbols, long double probabilities[num_symbols + 2], long double code_number) {
    long double sum = 0;
    for (int i = 1; i <= num_symbols + 1; i++) {
        if (code_number >= sum && code_number < sum + probabilities[i]) {
            return i;
        }
        sum += probabilities[i];
    }
    return num_symbols;
}

//Returns the sum of all probabilities up to a given index
long double sum_to_index(int num_symbols, long double probabilities[num_symbols + 2], int index) {
    long double sum = 0;
    for (int i = 0; i < index; i++) {
        sum += probabilities[i];
    }
    return sum;
}