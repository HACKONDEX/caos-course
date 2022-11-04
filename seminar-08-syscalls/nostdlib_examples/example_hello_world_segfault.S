    .intel_syntax noprefix
    .global _start
    .text

_start:
    mov rdi, 1
    mov rsi, 1
    lea rdx, str
    mov rcx, 8
    call syscall
    ret


str: .string "Hellow!\n"