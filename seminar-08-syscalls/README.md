# Linux System calls, `C` without libc

__Syscall__ __-__ is a userspace request of a kernel service. The syscall in our programm causes processor interruption and then the kernel handls the interrupt executing some code from kernel.

Syscall gives the programm ability to interact with the operating system and request some resources. For example sockets, physical-memory, connections to other hardware components like audio-card, battery, net-card and etc.

### Useful links

[Yakovlev's reading](https://github.com/victor-yacovlev/fpmi-caos/tree/master/practice/asm/nostdlib_baremetal)

[Articles about intteruptions](https://0xax.gitbooks.io/linux-insides/content/Interrupts/index.html)

[System calls: more theory](https://0xax.gitbooks.io/linux-insides/content/SysCall/linux-syscall-1.html)

## Syscalls in code

- In `stdlibc` there is `unistd.h` header with syscall functions. Which are wrappers for kernel syscalls. Wrappers just organize syscall number and arguments in other words give good interface for making syscalls.

#### Example

```C
#include <unistd.h>

int main() {
    char output[] = "Hellow!";
    write(1, output, sizeof(output));
    return 0;
}
```

--------------

- If we compile without `stdlib` the assembly code uses instruction `syscall` in `x86_64` and instruction `int` in 32bit architecture, to make a syscall. Of course we should first organize arguments. In register `rax` must be the number of the syscall. For example `1` is for syscall `write` and `60` for syscall `exit`. Then using `rdi`, `rsi`, `rdx`, `r10`, `r8` we pass the arguments.

- ___Note___ that if you want to use `syscall` asm instruction, than you must save all registers on stack of your programm. Standart function calling conventions doesn't work for `syscall`

- To make it easyer, we have implemented function [syscall](/seminar-08-syscalls/nostdlib_examples/syscall.S) which pushes registers on stack and calls the oppropriate syscall

## ASM and C examples of __nostdlib__ hello_world programm

- __Note__ without `stdlib` there is no main function required. Programm's entry point is the function `_start`

```
    .intel_syntax noprefix
    .global _start
    .text

_start:
    mov rdi, 1
    mov rsi, 1
    lea rdx, str
    mov rcx, 8
    call syscall
    mov rdi, 60
    mov rsi, 1
    call syscall


str: .string "Hellow!\n"
```

- There is header a file `asm/unistd_64.h` where we have definitions for syscall numbers, we should use them instead of bare numbers

- You can get acquainted [with syscalls here](https://filippo.io/linux-syscall-table/)

```C
#include <asm/unistd_64.h>

void _start() {
    char hellow[] = "Hellow!\n";
    syscall(__NR_write, 1, hellow, sizeof(hellow));
    syscall(__NR_exit, 0);
}
```

-------

## Syscall read and write

- `read` __-__ syscall to get content of files, pipes, terminal, fifo-pipes, sockets and etc. Returns the amount of bytes read from file-descriptor and `-1` if there was an error.

- `write` __-__ syscall to wrtie bytes into files, pipes, terminal, fifo-pipes, sockets and etc. Returns successfuly wrtitten bytes count and `-1` if there was an error

- Open `man 2 read` and `man 2 write` for more details

#### Example

```C
#include <asm/unistd_64.h>

typedef enum {
    BUFFER_SIZE = 256,
} constant_t;

void _start() {
    char buffer[BUFFER_SIZE];

    int read_count = syscall(__NR_read, 0, buffer, BUFFER_SIZE);

    syscall(__NR_write, 1, buffer, read_count);

    syscall(__NR_exit_group, 0);
}
```

## Syscall brk

- Program breakdown is the first position following the completion of the uninitialized data segment

- It can be changed using syscall `brk`

- In `unistd.h` `sbrk` function

#### Example

```C
#include <asm/unistd_64.h>
#include <stdio.h>
#include <stdint.h>

int64_t syscall(int64_t code, ...);

int main() {

    char* start = (void *)syscall(__NR_brk, 0);
    printf("Initial breakdown border %p\n", start);

    char * end = (void *)syscall(__NR_brk, (void*)start + 250000);
    printf("Border after allocating 25000 bytes %p\n", end);

    char * new_end = (void *)syscall(__NR_brk, (void*)end + 250000);
    printf("New border after allocating additional 25000 bytes %p\n", new_end);

    long long diff = end - start;
    printf("Difference of addresses(end - start):     %lld\n", diff);

    long long new_diff = new_end - end;
    printf("Difference of addresses(new_end - end):   %lld\n", new_diff);

    long long big_diff = new_end - start;
    printf("Difference of addresses(new_end - start): %lld\n", big_diff);

    return 0;
}
```

##### Without stdlib

```C
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
```


