#include <stdio.h>

int main() {
    int d[5], c[8], s[4];
    int i, error_pos = 0;

    // Input data bits (d1 to d4)
    printf("Enter 4-bit data (d1 d2 d3 d4): ");
    for (i = 1; i <= 4; i++) {
        scanf("%d", &d[i]);
    }

    // Assign data bits to codeword positions
    // Positions: 1,2,4 are parity bits
    c[3] = d[1];
    c[5] = d[2];
    c[6] = d[3];
    c[7] = d[4];

    // Calculate parity bits (even parity)
    c[1] = (c[3] + c[5] + c[7]) % 2;
    c[2] = (c[3] + c[6] + c[7]) % 2;
    c[4] = (c[5] + c[6] + c[7]) % 2;

    // Display generated codeword
    printf("\nGenerated Hamming Code: ");
    for (i = 7; i >= 1; i--) {
        printf("%d ", c[i]);
    }

    // Input received codeword
    printf("\nEnter received 7-bit code: ");
    for (i = 7; i >= 1; i--) {
        scanf("%d", &c[i]);
    }

    // Calculate syndrome bits
    s[1] = (c[1] + c[3] + c[5] + c[7]) % 2;
    s[2] = (c[2] + c[3] + c[6] + c[7]) % 2;
    s[3] = (c[4] + c[5] + c[6] + c[7]) % 2;

    // Compute error position
    error_pos = s[1]*1 + s[2]*2 + s[3]*4;

    printf("\nSyndrome: %d%d%d", s[3], s[2], s[1]);

    if (error_pos == 0) {
        printf("\nNo error in received code.\n");
    } else {
        printf("\nError at position: %d (from right)\n", error_pos);

        // Correct the bit
        c[error_pos] ^= 1;

        printf("Corrected codeword: ");
        for (i = 7; i >= 1; i--) {
            printf("%d ", c[i]);
        }
        printf("\n");
    }

    return 0;
}