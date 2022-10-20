    .intel_syntax noprefix

    .extern A
    .text                                  
    .globl very_important_function 

very_important_function:

    push   r12  
    mov    r12, 0                    //  i == r12 = 0 

    push   r13 
    mov    r13, rdi                  //  r13 = N

    sub    rsp, 8                    //  allocate 8 bytes on stack

.loop_begin:
    cmp    r12, r13                  //  if (i >= N) 
    jae    .loop_end                 //  break

    lea    rdi, .fmt_scanf[rip]      //  load into `rdi` char* "%d"
    mov    rsi, rsp                  //  load into `rsi` pointer to int32_t on stack

    call   scanf                     //  call scanf

    movsxd rsi, DWORD PTR [rsp]      //  load into `rsi` int32_t value from stack
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
