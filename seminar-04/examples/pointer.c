#include <inttypes.h>

char compare_and_exchange(int64_t* contained, int64_t* expected, int64_t value) {
    if (*contained == *expected) {
        *contained = value;
        return 1;
    }
    *expected = *contained;
    return 0;
}