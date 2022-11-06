#include <asm/unistd_64.h>

void _start() {
    char hellow[] = "Hellow!\n";
    syscall(__NR_write, 1, hellow, sizeof(hellow) - 1); // -1 for '\0'
    syscall(__NR_exit_group, 0);
}