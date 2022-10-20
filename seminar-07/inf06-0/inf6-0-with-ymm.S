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
