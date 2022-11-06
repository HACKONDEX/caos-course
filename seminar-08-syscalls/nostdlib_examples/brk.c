#include <asm/unistd_64.h>
#include <stdio.h>
#include <stdint.h>

int64_t syscall(int64_t code, ...);
// __asm__(R"(
// syscall:
//     push r9
//     push r8
//     push rcx
//     push rdx
//     push rsi
//     push rdi
//     pop rax
//     pop rdi
//     pop rsi
//     pop rdx
//     pop r10
//     pop r8
//     syscall
//     ret
//     )");

int main() {

    char* start = (void *)syscall(__NR_brk, 0);
    printf("Initial breakdown border                           %p\n", start);

    char * end = (void *)syscall(__NR_brk, (void*)start + 250000);
    printf("Border after allocating 25000 bytes                %p\n", end);

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