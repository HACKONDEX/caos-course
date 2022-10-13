# __ASM x86-64__

- x86-64 is another processor architecture

- Assembly code for this architecture has two syntaxes `AT&T` and `intel`, we will use `intel` syntax

## Compilation and execution

- on linux use default gcc compiler with flags 

- Disassembly example

      gcc -m64 -masm=intel -S -O3 code.c -o code.S

- One compilation unit

      gcc -m64 -masm=intel disasom_example.S -o run.exe

- Many compilation units

      gcc -m64 -masm=intel disasom_exmaple.S main.c -o run.exe

- You don't need emulator for running if your processor mark is `intel` or `amd`

      ./run.exe

---------------------------

### <center>__x86-64__ registers</center>

- Has `16 general purpose registers` and `8 large registers` for floating point numbers operations

- `rax`, `rbx`, `rcx`, `rdx`, `rsi`, `rdi` __-__ general purpose, for any operations

- `rsp` __-__ stack pointer

- `rbp` __-__ pointer to the begging of the stack frame

- `r8-r15` __-__ more registers

- `xmm0-xmm7` __-__ floating point registers

-----------------

- General arguments functions receive in registers `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9` in the given order

- If function expects more than `6` arguments, they should be sotred on stack

- Function __return value__ is stored in register `rax`

- ___Note___ that rules above don't apply to floating point types(will discuss it on next lesson)

- __Callee__ function must save values of registers `rbx`, `rbp`, `r12-r15`

-----------------

- __Stack__ must always be aligned with ___16___ bytes

#### Compiler generated code example

```C
#include <inttypes.h>
#include <stdio.h>

int64_t calculate(int32_t a, int32_t b, int64_t x) {
    return (a + b) * b + x;
}

int main() {
    int32_t num = 0;
    scanf("%" PRId32, &num);

    int64_t result = calculate(num, 1, 0);

    printf("%" PRId64 "\n", result);
    return 0;
}
```

- We will look at important code lines

```
	.intel_syntax noprefix
	.text
	.globl	calculate
calculate:
	endbr64
	lea	eax, [rdi+rsi]
	imul	eax, esi
	cdqe
	add	rax, rdx
	ret

.LC0
	.string	"%d"
.LC1:
	.string	"%ld\n"

	.globl	main
main:
.LFB24:
	endbr64
	sub	rsp, 24
	lea	rdi, .LC0[rip]
	xor	eax, eax
	lea	rsi, 4[rsp]
	mov	DWORD PTR 4[rsp], 0
	call	__isoc99_scanf@PLT
	mov	eax, DWORD PTR 4[rsp]
	mov	edi, 1
	lea	rsi, .LC1[rip]
	lea	edx, 1[rax]
	xor	eax, eax
	movsx	rdx, edx
	call	__printf_chk@PLT
	mov	rax, QWORD PTR 8[rsp]
	jne	.L6
	xor	eax, eax
	add	rsp, 24
	ret

```


