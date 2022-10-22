# __x86-64__  __AVX__

- ___NOTE___ testing system of [ejudge](https://ejudge.atp-fivt.org) is `Fedor`, and it doesn't use `ASLR`. If you are using `Ubuntu` than you should compile with option `-no-pie`.

- Large registers for floating point numbers

- Registers `xmm0-xmm7` with size ___128___ bits

- [AVX instructions for asm](https://docs.oracle.com/cd/E36784_01/html/E36859/gntbd.html)

- [Official intrices documentation](https://www.laruence.com/sse/#techs=AVX,AVX2)

## examples

### Task inf-I-06-0: asm-x86/avx/intro

- Solution in the `C` language

```C
#include <stdio.h>

double very_important_function(size_t N, const float *A, const float *B, float *R) {
    double sum = 0;
    for (size_t i = 0; i < N; ++i) {
        R[i] = A[i] + B[i];
        sum += R[i];
    }
    return sum / N;
}
```

- Dissasembly of the solution

```
	.intel_syntax noprefix
	.text
	.globl	very_important_function
very_important_function:
.LFB23:
	endbr64
	test	rdi, rdi
	je	.L4
	xor	eax, eax
	pxor	xmm0, xmm0
.L3:
	movss	xmm1, DWORD PTR [rsi+rax*4]
	addss	xmm1, DWORD PTR [rdx+rax*4]
	movss	DWORD PTR [rcx+rax*4], xmm1
	add	rax, 1
	cvtss2sd	xmm1, xmm1
	addsd	xmm0, xmm1
	cmp	rdi, rax
	jne	.L3
	pxor	xmm1, xmm1
	cvtsi2sd	xmm1, rdi
	divsd	xmm0, xmm1
	ret
.L4:
	pxor	xmm1, xmm1
	pxor	xmm0, xmm0
	cvtsi2sd	xmm1, rdi
	divsd	xmm0, xmm1
	ret

```

- Human written assembly solution

```
    .intel_syntax noprefix

    .text
    .global very_important_function

very_important_function:
    endbr64
    //       rdi = N
    //       rsi = float *A
    //       rdx = float *B
    //       rcx = float *R

    pxor     xmm0, xmm0                        //  sum == xmm0 = 0
    mov      rax, 0                            //  i == rax = 0

.loop_begin:

    cmp      rax, rdi                           //  if (i >= N)
    jae      .loop_end                          //  break

    movaps   xmm1, XMMWORD PTR [rsi + rax * 4]  //  load 4 consecutive floats from pointer(to aligned memory)
    addps    xmm1, XMMWORD PTR [rdx + rax * 4]  //  add to each 4 bytes of `xmm1` loaded 4 consecutive floats

    movaps   XMMWORD PTR [rcx + rax * 4], xmm1  //  store 4 consecutive floats from `xmm1` by pointer

    addps    xmm0, xmm1                         //  add packed floats from `xmm1` to `xmm0`    
    
    add      rax, 4                             //  i += 4
    jmp      .loop_begin    
    
.loop_end:

    haddps   xmm0, xmm0                         //  horizontal add packed-floats
    haddps   xmm0, xmm0                         //  horiznotal add packed-floats
    cvtss2sd xmm0, xmm0                         //  converts float to double 

    cvtsi2sd xmm1, rdi                          //  converts doubleword integer to double
    divsd    xmm0, xmm1                         //  divides scalar double values

    ret                                         // return value should be in xmm0
```

- If the processes supports AVX-2 than we can use `ymm0-ymm15` larger registers with size ___256___ bits

```
    .intel_syntax noprefix

    .text
    .global very_important_function

very_important_function:
    endbr64
    //       rdi = N
    //       rsi = float *A
    //       rdx = float *B
    //       rcx = float *R

    vpxor    ymm0, ymm0, ymm0                  //  sum == xmm0 = 0
    mov      rax, 0                            //  i == rax = 0

.loop_begin:

    cmp      rax, rdi                           //  if (i >= N)
    jae      .loop_end                          //  break

    vmovaps   ymm1, YMMWORD PTR [rsi + rax * 4]
    vmovaps   ymm2, YMMWORD PTR [rdx + rax * 4]
    vaddps    ymm1, ymm1, ymm2  

    vmovaps   YMMWORD PTR [rcx + rax * 4], ymm1

    addps    xmm0, XMMWORD PTR [rcx + rax * 4]
    mov       r8, rax
    add       r8, 4
    addps    xmm0, XMMWORD PTR [rcx + r8 * 4]
    
    add      rax, 8                             //  i += 8
    jmp      .loop_begin    
    
.loop_end:

    haddps   xmm0, xmm0                         //  horizontal add packed-floats
    haddps   xmm0, xmm0                         //  horiznotal add packed-floats

    cvtss2sd xmm0, xmm0

    cvtsi2sd xmm1, rdi                          //  converts doubleword integer to double
    divsd    xmm0, xmm1                         //  divides scalar double values

    ret                                         // return value should be in xmm0
```

---------------------------

### Another example

```C
#include <inttypes.h>
#include <stdio.h>

#define N 4

int main() {
    float a[N] = {0, 0, 0, 0};
    float b[N] = {1.5, 2.5, 3.5, 4.5};

    double sum = 0.0;

    for (size_t i = 0; i < N; ++i) {
        scanf("%f", &a[i]);
        a[i] *= b[i];

        if (i != 0) {
            a[i] /= i;
        }
        sum += a[i];
    }

    printf("%f\n", sum);
    return 0;
}
```

- My asm code of code above

```
    .intel_syntax noprefix

    .text
    .global main

main:
    endbr64
    push     rbx
    sub      rsp, 32                           // allocate 16 bytes on stack
    

    pxor     xmm0, xmm0                        //  sum == xmm0 = 0
    mov      rbx, 0                            //  i == rbx = 0

.loop_begin:

    cmp      rbx, 4                            //  if (i >= 4)
    jae      .loop_end                         //  break

    vmovsd   QWORD PTR [rsp + 16], xmm0        //  store low double from `xmm0` on stack
    lea      rdi, .scanf_fmt_str[rip]          //  load char*

    mov      rsi, rbx                          //  rsi = i
    imul     rsi, 4                            //  rsi == i * 4
    add      rsi, rsp                          //  rsi == rsp + i * 4

    call scanf                                 // call scanf("%f", &a[i])

    vmovsd   xmm0, QWORD PTR [rsp + 16]                    //  xmm0 == sum
    vmovss   xmm1, DWORD PTR [rsp + rbx * 4]
    movupd   xmm2, XMMWORD PTR [.label_array_b + rbx * 8]  //  load double b[i]
    cvtsd2ss xmm2, xmm2                                    //  cast double to float
    mulss    xmm1, xmm2                                    //  a[i] *= b[i]
    
    
    cmp rbx, 0                                 //  if (i != 0)
    je .end_divide

.divide:
    cvtsi2ss xmm2, rbx                         //  cast `i` to float
    divss    xmm1, xmm2                        //  a[i] /= i;

.end_divide:

    cvtss2sd xmm1, xmm1                        //  cast float to double
    addsd    xmm0, xmm1                        //  sum += a[i]
    add      rbx, 1                            //  ++i
    jmp      .loop_begin

.loop_end:


    lea      rdi, .printf_fmt_str[rip]         // load cahr* "%f\n"

    call printf                                // printf("%f\n", sum)

    mov      rax, 0
    add      rsp, 32
    pop      rbx

    ret                                         


.section .data
.label_array_b:
    .double 1.5
    .double 2.5
    .double 3.5
    .double 4.5

.section .rodata
.scanf_fmt_str:
    .string "%f"
.printf_fmt_str:
    .string "%f\n"
```