#include <stdio.h>

double very_important_function(size_t N, const float *A, const float *B, float *R) {
    double sum = 0;
    for (size_t i = 0; i < N; ++i) {
        R[i] = A[i] + B[i];
        sum += R[i];
    }
    return sum / N;
}
