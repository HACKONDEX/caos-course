#include <inttypes.h>
#include <limits.h>
#include <stdio.h>

int check_signed(int x) {
    return (x + 1) > x;
}

int check_unsigned(unsigned int x) {
    return (x + 1) > x;
}

int main() {
    printf("check unsigned for UINTMAX returned  %d\n", check_unsigned(UINT_MAX));
    int64_t value = INT64_MAX;
    printf("value + 1 == %" PRId64 "\n", value + 1);
    ++value;
    printf("after increment value == %" PRId64 "\n", value);
    uint64_t uint_value = 0;
    printf("uint 0 - 1 == %" PRIu64 "\n", uint_value - 1u);
    --uint_value;
    printf("uint 0 after decrement == %" PRIu64 "\n", uint_value);
    printf("check signed for INTMAX returned  %d\n", check_signed(INT_MAX));
    return 0;
}
