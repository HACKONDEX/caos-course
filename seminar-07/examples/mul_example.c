#include <inttypes.h>
#include <stdio.h>

#define N 4

int main() {
    float a[N] = {0, 0, 0, 0};
    float b[N] = {1.5, 2.5, 3.5, 4.5};

    double sum = 0.0;

    for (size_t i = 0; i < N; ++i) {
        scanf("%f", &a[i]);
        a[i] *= b[i];

        if (i != 0) {
            a[i] /= i;
        }
        sum += a[i];
    }

    printf("%f\n", sum);
    return 0;
}
