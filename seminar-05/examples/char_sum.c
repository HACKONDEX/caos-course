#include <inttypes.h>
#include <stdio.h>

char char_sum(char a, char b) {
    return a + b;
}

int main() {
    char first = 0;
    char second = 0;

    scanf("%c %c", &first, &second);

    char sum = char_sum(first, second);

    printf("sum of `%c` and `%c` equals to symbol `%c`\n", first, second, sum);
    printf("Or equals to number %" PRId8 "\n", sum);

    return 0;
}