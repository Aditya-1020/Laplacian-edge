#include <stdio.h>

int main() {
    // Define the 3x3 matrix
    float matrix[3][3] = {
        {1.0 / 16, 2.0 / 16, 1.0 / 16},
        {2.0 / 16, 4.0 / 16, 2.0 / 16},
        {1.0 / 16, 2.0 / 16, 1.0 / 16}
    };

    // Print the matrix
    printf("Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
