#include <limits.h>
#include <stdio.h>

unsigned int get_remains(unsigned int x, unsigned int y) {
    return x % y;
}

unsigned int sum(unsigned int x, unsigned int y) {
    if (x + y < x) {
        return UINT_MAX;
    }
    return x + y;
}

int main() {
    unsigned int x = 13;
    unsigned int y = 20;

    printf("The remainder of %u devided by %u is %u \n", x, y, get_remains(x, y));

    printf("Sum of %u and %u is %u \n", x, y, sum(x, y));

    printf("Sum of %u and 1 is %u which is the UINT_MAX \n", UINT_MAX, sum(1, UINT_MAX));

    return 0;
}
