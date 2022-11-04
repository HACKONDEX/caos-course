#include <asm/unistd_64.h>

void _start() {
    char hellow[] = "Hellow!\n";
    syscall(__NR_write, 1, hellow, sizeof(hellow));
    syscall(__NR_exit, 0);
}