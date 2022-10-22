#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const size_t N = 8;

int main() {
    double a[8] = {11.1, 22.2, 33.3, 77.7, 11.1, 11.1, 11.1, 11.1};
    double* b = calloc(N, sizeof(double));
    for (size_t i = 0; i < N; ++i) {
        scanf("%lf", &b[i]);
    }

    __m256d pack_a = _mm256_loadu_pd(a);
    __m256d pack_b = _mm256_loadu_pd(b);

    pack_b = _mm256_mul_pd(pack_a, pack_b);
    _mm256_storeu_pd(b, pack_b);

    pack_b = _mm256_loadu_pd(b + 2);
    pack_b = _mm256_add_pd(pack_a, pack_b);

    _mm256_storeu_pd(b + 2, pack_b);

    for (size_t i = 0; i < N; ++i) {
        printf("%lf ", b[i]);
    }

    return 0;
}