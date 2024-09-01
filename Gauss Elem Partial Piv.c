#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3  // Number of variables

void forwardElimination(double matrix[N][N+1]);
void backSubstitution(double matrix[N][N+1], double* solution);
void partialPivoting(double matrix[N][N+1], int k);
int checkZeroDiagonal(double matrix[N][N+1]);

int main() {
    double matrix[N][N+1];
    double solution[N];

    // Reading input from the file
    FILE *inputFile = fopen("input_2a.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            fscanf(inputFile, "%lf", &matrix[i][j]);
        }
    }
    fclose(inputFile);

    // Perform forward elimination with partial pivoting
    forwardElimination(matrix);

    // Perform back substitution
    backSubstitution(matrix, solution);

    // Print the results to output file
    FILE *outputFile = fopen("output_2a.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Cannot open output file.\n");
        return 1;
    }

    // Print the final augmented matrix
    fprintf(outputFile, "The final augmented matrix after forward elimination is:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            fprintf(outputFile, "%lf ", matrix[i][j]);
        }
        fprintf(outputFile, "\n");
    }

    // Print the solution
    fprintf(outputFile, "\nThe solution is:\n");
    for (int i = 0; i < N; i++) {
        fprintf(outputFile, "x%d = %lf\n", i + 1, solution[i]);
    }

    fclose(outputFile);
    return 0;
}

void forwardElimination(double matrix[N][N+1]) {
    for (int k = 0; k < N-1; k++) {
        // Apply partial pivoting
        partialPivoting(matrix, k);

        for (int i = k+1; i < N; i++) {
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k; j <= N; j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }
}

void backSubstitution(double matrix[N][N+1], double* solution) {
    for (int i = N-1; i >= 0; i--) {
        solution[i] = matrix[i][N];
        for (int j = i+1; j < N; j++) {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i];
    }
}

void partialPivoting(double matrix[N][N+1], int k) {
    int maxIndex = k;
    double maxValue = fabs(matrix[k][k]);

    for (int i = k+1; i < N; i++) {
        if (fabs(matrix[i][k]) > maxValue) {
            maxValue = fabs(matrix[i][k]);
            maxIndex = i;
        }
    }

    if (maxIndex != k) {
        // Swap rows
        for (int j = 0; j <= N; j++) {
            double temp = matrix[k][j];
            matrix[k][j] = matrix[maxIndex][j];
            matrix[maxIndex][j] = temp;
        }
    }
}
