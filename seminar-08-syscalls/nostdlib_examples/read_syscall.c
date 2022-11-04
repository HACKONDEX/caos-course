#include <asm/unistd_64.h>

typedef enum {
    BUFFER_SIZE = 256,
} constant_t;

void _start() {
    char buffer[BUFFER_SIZE];

    int read_count = syscall(__NR_read, 0, buffer, BUFFER_SIZE);

    syscall(__NR_write, 1, buffer, read_count);

    syscall(__NR_exit, 0);
}