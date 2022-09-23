#include <inttypes.h>
#include <limits.h>
#include <stdio.h>

int main() {
    printf("int8_t   %d %" PRId8 "  %" PRId8 "\n", sizeof(int8_t), INT8_MAX, INT8_MIN);
    printf("int16_t  %d %" PRId16 " %" PRId16 "\n", sizeof(int16_t), INT16_MAX, INT16_MIN);
    printf("int32_t  %d %" PRId32 " %" PRId32 "\n", sizeof(int32_t), INT32_MAX, INT32_MIN);
    printf("int64_t  %d %" PRId64 " %" PRId64 "\n", sizeof(int64_t), INT64_MAX, INT64_MIN);
    printf("uint8_t  %d %" PRIu8 "  %" PRIu8 "\n", sizeof(uint8_t), UINT8_MAX, 0);
    printf("uint16_t %d %" PRIu16 " %" PRIu16 "\n", sizeof(uint16_t), UINT16_MAX, 0);
    printf("uint32_t %d %" PRIu32 " %" PRIu32 "\n", sizeof(uint32_t), UINT32_MAX, 0);
    printf("uint64_t %d %" PRIu64 " %" PRIu64 "\n", sizeof(uint64_t), UINT64_MAX, 0);

    printf("int %d %d\n", sizeof(int), INT_MAX, INT_MIN);
    printf("long long %d %lld\n", sizeof(long long ), LLONG_MAX, LLONG_MIN);

    return 0;
}