#include <sys/syscall.h>
#include <stdint.h>

int64_t syscall(int64_t code, ...);

void int_to_symbol(uint64_t i, char* s, int* len) {
    int clen = 0;
    for (int ic = i; ic; ic /= 10, ++clen);
    clen = clen ?: 1;
    s[clen] = '\0';
    for (int j = 0; j < clen; ++j, i /= 10) {
        s[clen - j - 1] = '0' + i % 10;
    }
    *len = clen;
}

int print_int(int64_t i) {
    char s[40];
    int len;
    int_to_symbol(i, s, &len);
    return syscall(SYS_write, 1, s, len);
}


void _start() {
    const int size = 100 * 1000;
    int* data_start = (void*)syscall(SYS_brk, 0);
    int* data_end = (void*)syscall(SYS_brk, (int*)data_start + size);

    data_start[0] = 1;
    for (int i = 1; i < (data_end - data_start); ++i) {
        data_start[i] = data_start[i - 1] + 1;
    }

    for (int i = 1; i < (data_end - data_start); ++i) {
        print_int(data_start[i]);
    }

    syscall(SYS_exit_group, 0);
}