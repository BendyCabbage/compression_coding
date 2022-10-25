#include <stdio.h>
#include <assert.h>

long double sum_to_index(
    int num_symbols, long double probabilities[num_symbols + 2], 
    int index
);

int main (void) {
    //Currently only encoding

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

long double sum_to_index(int num_symbols, long double probabilities[num_symbols + 2], int index) {
    long double sum = 0;
    for (int i = 0; i < index; i++) {
        sum += probabilities[i];
    }
    return sum;
}