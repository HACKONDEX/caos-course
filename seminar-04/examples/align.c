#include <inttypes.h>
#include <stdio.h>

struct A {
    char flag_x;
    char flag_y;
    int32_t coord_x;
    int32_t coord_y; 
};

struct B {
    int32_t coord_x;
    int32_t coord_y;
    char flag_x;
    char flag_y;
};

struct C {
    char flag_x;
    int32_t coord_x;
    char flag_y;
    int32_t coord_y;
};

struct D {
    int32_t coord_x;
    char flag_x;
    int32_t coord_y;
    char flag_y;
};

struct E {
    char flag_x;
    int32_t coord_x;
    int32_t coord_y;
    char flag_y;
};


int main() {
    printf("%ld\n", sizeof(struct A));

    printf("%ld\n", sizeof(struct B));

    printf("%ld\n", sizeof(struct C));
    printf("%ld\n", sizeof(struct D));
    printf("%ld\n", sizeof(struct E));
    return 0;

}