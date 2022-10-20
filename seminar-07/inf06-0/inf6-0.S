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
