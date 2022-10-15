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

- ___Note___ At the moment of entering a function there are already 8 allocated bytes on stack, which stand for function return address. So if the function is going to use data from stack, it should allocate `count * 8` bytes where count must be an `odd` number

---------------------------------------------

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
----------------------------------------------------------

- Let's solve task 5-0

- So we just need to write this `C` code using assembly `x86-64` wiht `intel` syntax

```C
#include <inttypes.h>
#include <stdio.h>

extern int *A;

void very_important_function(size_t N) {
    for (size_t i = 0; i < N; ++i) {
        int32_t num = 0;
        scanf("%d", &num);
        int64_t result = num;
        result *= A[i];
        printf("%d\n", result);
    }    
}
```

- Assembly variant

```
	.intel_syntax noprefix

	.text                                  
	.globl very_important_function 

very_important_function:

	endbr64

	push   r12  
	mov    r12, 0                    //  i == r12 = 0 

    push   r13 
	mov    r13, rdi			         //  r13 = N

	sub    rsp, 8                    //  allocate 8 bytes on stack

.loop_begin:
	cmp    r12, r13                  //  if (i >= N) 
	jae    .loop_end                 //  break

	lea    rdi, .fmt_scanf[rip]      //  load into `rdi` char* "%d"
    mov    rsi, rsp                  //  load into `rsi` pointer to int32_t on stack

    call   scanf                     //  call scanf

	movsxd rsi, [rsp]                //  load into `rsi` int32_t value from stack
    mov    rcx, A[rip]               //  load into `rcx` address of A

	movsxd rcx, [rcx + 4 * r12]      //  load into `rcx` *(A + i * 4)
    imul   rsi, rcx                  //  store in `rax` value of (rsi * rcx)

	lea    rdi, .fmt_printf[rip]     //  load into `rdi` char* "%lld\n"

    call   printf                    // call printf

    inc    r12                       // increment `r12` i. e. `++i`
    jmp    .loop_begin     


.loop_end:
	add    rsp, 8                    // free allocated stack memory

    pop    r13                       // restore saved on stack value of `r13` 
    pop    r12                       // restore saved on stack value of `r12`

	ret

	.section .rodata
.fmt_scanf:
    .string "%d"
.fmt_printf:
    .string "%lld\n"

```


