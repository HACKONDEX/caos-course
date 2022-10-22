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
