#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4  // Number of variables
#define EPSILON 1e-7  // Convergence criterion
#define MAX_ITERATIONS 1000  // Maximum number of iterations

void gaussSeidel(double matrix[N][N+1], double* solution);

int main() {
    double matrix[N][N+1];
    double solution[N] = {0};  // Initial guess

    // Reading input from the file
    FILE *inputFile = fopen("input_3.txt", "r");
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

    // Perform Gauss-Seidel iteration
    gaussSeidel(matrix, solution);

    // Print the results to the output file
    FILE *outputFile = fopen("output_3.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Cannot open output file.\n");
        return 1;
    }

    // Print the solution
    fprintf(outputFile, "The solution is:\n");
    for (int i = 0; i < N; i++) {
        fprintf(outputFile, "x%d = %lf\n", i + 1, solution[i]);
    }

    fclose(outputFile);
    return 0;
}

void gaussSeidel(double matrix[N][N+1], double* solution) {
    double oldSolution[N];
    int iterations = 0;

    while (iterations < MAX_ITERATIONS) {
        for (int i = 0; i < N; i++) {
            oldSolution[i] = solution[i];
        }

        for (int i = 0; i < N; i++) {
            double sum = matrix[i][N];  // Start with the constant term
            for (int j = 0; j < N; j++) {
                if (i != j) {
                    sum -= matrix[i][j] * solution[j];
                }
            }
            solution[i] = sum / matrix[i][i];
        }

        // Check for convergence
        int converged = 1;
        for (int i = 0; i < N; i++) {
            if (fabs(solution[i] - oldSolution[i]) > EPSILON) {
                converged = 0;
                break;
            }
        }

        if (converged) {
            break;
        }

        iterations++;
    }

    if (iterations == MAX_ITERATIONS) {
        printf("Warning: Maximum iterations reached without convergence.\n");
    }
}
