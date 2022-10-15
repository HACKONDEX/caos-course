#include <inttypes.h>
#include <stdio.h>

int64_t calculate(int32_t a, int32_t b, int64_t x) {
    return (a + b) * b + x;
}

int main() {
    int32_t num = 0;
    scanf("%" PRId32, &num);

    int64_t result = calculate(num, 1, 0);

    printf("%" PRId64 "\n", result);
    return 0;
}