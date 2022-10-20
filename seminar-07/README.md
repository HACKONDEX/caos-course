# __x86-64__  __AVX__

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

- If the processes supports AVX-2 than we can use `ymm0-ymm16` larger registers with size ___256___ bits

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