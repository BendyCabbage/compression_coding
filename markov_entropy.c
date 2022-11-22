//Calculates the Markov Entropy

#include <stdio.h>
#include <math.h>
#include <assert.h>

double calculate_entropy(int radix, int num_probabilities, double probabilities[num_probabilities]);

int main (void) {
    int radix;
    printf("Enter radix: ");
    scanf("%d", &radix);
    assert(radix > 1);

    int num_columns;
    printf("Enter the number of columns: ");
    scanf("%d", &num_columns);

    int num_probabilities;
    printf("Enter the number of probabilities in each column: ");
    scanf("%d", &num_probabilities);

    int equilibrium_probabilities[num_columns];

    double probabilities[num_probabilities * num_columns];
    printf("Enter the probabilities as a decimal (p1 p2 p3...): ");
    for (int i = 0; i < num_probabilities; i++) {
        scanf("%lf", &(probabilities[i]));
    }
    printf("Markov Entropy: %lf\n", calculate_entropy(radix, num_probabilities, probabilities));
}

double calculate_entropy(int radix, int num_probabilities, double probabilities[num_probabilities]) {
    double entropy = 0;
    double denominator = 1 / log(radix);
    for (int i = 0; i < num_probabilities; i++) {
        entropy += probabilities[i] * log(probabilities[i]) * denominator;
    }
    entropy *= -1;

    return entropy;
}