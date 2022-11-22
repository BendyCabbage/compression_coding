//Implementes Shannon Fano coding

#include <stdio.h>
#include <math.h>
#include <assert.h>

void calculate_codeword_lengths(
    int radix,
    int num_probabilities, 
    double probabilities[num_probabilities], 
    int codeword_lengths[num_probabilities]
);

int main (void) {
    int radix;
    printf("Enter radix: ");
    scanf("%d", &radix);
    assert(radix > 1);

    int num_probabilities;
    printf("Enter the number of probabilities: ");
    scanf("%d", &num_probabilities);

    double probabilities[num_probabilities];
    printf("Enter the probabilities as a decimal (p1 p2 p3...): ");
    for (int i = 0; i < num_probabilities; i++) {
        scanf("%lf", &(probabilities[i]));
    }
    int codeword_lengths[num_probabilities];
    calculate_codeword_lengths(radix, num_probabilities, probabilities, codeword_lengths);

    double average_codeword_length = 0;
    for (int i = 0; i < num_probabilities; i++) {
        average_codeword_length += probabilities[i] * codeword_lengths[i];
    }
    printf("Average codeword length: %lf\n", average_codeword_length);

    printf("Codeword lengths: ");
    for (int i = 0; i < num_probabilities; i++) {
        printf("%d ", codeword_lengths[i]);
    }
}

void calculate_codeword_lengths(
    int radix,
    int num_probabilities, 
    double probabilities[num_probabilities], 
    int codeword_lengths[num_probabilities]
) {
    double denominator = 1 / log(radix);
    for (int i = 0; i < num_probabilities; i++) {
        codeword_lengths[i] = ceil(-1 * log(probabilities[i]) * denominator);
    }
    return;
}

