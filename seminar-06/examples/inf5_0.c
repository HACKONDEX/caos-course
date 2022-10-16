#include <inttypes.h>
#include <stdio.h>

extern int *A;

void very_important_function(size_t N) {
    for (size_t i = 0; i < N; ++i) {
        int32_t num = 0;
        scanf("%d", &num);
        int64_t result = num;
        result *= A[i];
        printf("%" PRId64 "\n", result);
    }    
}