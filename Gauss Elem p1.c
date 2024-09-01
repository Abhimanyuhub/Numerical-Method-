#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4  // Number of variables

void forwardElimination(double matrix[N][N+1]);
void backSubstitution(double matrix[N][N+1], double* solution);
int checkUniqueSolution(double matrix[N][N+1]);

int main() {
    double matrix[N][N+1];
    double solution[N];

    // Reading input from the file
    FILE *inputFile = fopen("input_1.txt", "r");
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

    // Perform forward elimination
    forwardElimination(matrix);

    // Check if the system has a unique solution, multiple solutions, or no solution
    int status = checkUniqueSolution(matrix);

    FILE *outputFile = fopen("output_1.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Cannot open output file.\n");
        return 1;
    }

    if (status == 0) {
        fprintf(outputFile, "The system has no unique solution.\n");
    } else {
        // Perform back substitution
        backSubstitution(matrix, solution);

        // Print the upper triangular matrix and solution
        fprintf(outputFile, "The final augmented matrix after forward elimination is:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= N; j++) {
                fprintf(outputFile, "%lf ", matrix[i][j]);
            }
            fprintf(outputFile, "\n");
        }

        fprintf(outputFile, "\nThe system has a unique solution:\n");
        for (int i = 0; i < N; i++) {
            fprintf(outputFile, "x%d = %lf\n", i + 1, solution[i]);
        }
    }

    fclose(outputFile);
    return 0;
}

void forwardElimination(double matrix[N][N+1]) {
    for (int k = 0; k < N-1; k++) {
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

int checkUniqueSolution(double matrix[N][N+1]) {
    for (int i = 0; i < N; i++) {
        if (matrix[i][i] == 0) {
            return 0; // No unique solution
        }
    }
    return 1; // Unique solution
}
