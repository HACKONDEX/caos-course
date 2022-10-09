    .text
    .global main

main:
    sub sp, sp, 32      // allocate 32 bytes on stack
    str lr, [sp, 24]    // save `lr` on stack

    mov x0, 50          // store in `x0` 50, amount of elements in future allocated memory
    mov x1, 1           // store in `x1` 1, 1 is the sizeof(char)

    bl calloc           // call calloc

    str x0, [sp, 16]    // save `x0` on stack
    mov x1, x0          // copy `x0` into `x1`
    adr x0, fmt_str     // store in `x0` char* for "%s"

    bl scanf            // call scanf

    // Here we prepare registers for `cycle for` to calculate length of the string
    ldr x0, [sp, 16]    // x0 == char* str
    mov x1, 0           // x1 == i = 0
    mov x2, 0           // x2 = '\0'
    mov x3, 0           // x3 == len = 0

.loop_begin_1:          // cycle for
    ldrsb x4, [x0, x1]  // x4 = str[x1]
    cmp x4, x2          // compare str[i] wiht '\0'
    beq .loop_end_1     // if equal break from cycle
    add x3, x3, 1       // ++len
    add x1, x1, 1       // ++i
    b .loop_begin_1     // new cycle iteration

.loop_end_1:

    str w3, [sp, 12]    // store 'x3` aka calculated `len` on stack
    adr x0, append_str  // store in `x0` char* ".suffix\0"

    bl strlen           // call function strlen(It returns length of the string)
                        // so instead of writing lines 19-31, we could have called `strlen`

    mov x3, 0           // reset `x3` to zero
    ldr w3, [sp, 12]    // w3 == i = len (w3 because we stored uin32_t value on stack)
                        // and we should load only 4 bytes to get correct len
                        // after reseting `x3` and loading 4 bytes from stack
                        // we have value of `len` in `x3` and can use `x3`

    // prepare registers for copying cycle
    mov x4, x3          // x4 = len, x3 == i
    add x0, x0, x4      // x0 = len + append_len
    adr x1, append_str  // x1 = char* append_str
    ldr x2, [sp, 16]    // x2 = char* str

.loop_begin_2:
    cmp x3, x0          // compare lengths and index
    bge .loop_end_2     // break if out of range
    sub x5, x3, x4      // x5 = i - len
    ldrsb w6, [x1, x5]  // load char `append_str[i - len]` by pointer
    strb w6, [x2, x3]   // store loaded char(str[i] = append_str[i - len])
    add x3, x3, 1       // ++i
    b .loop_begin_2     // new iteration

.loop_end_2:

    adr x0, fmt_str     // store in `x0` char* "%s"
    mov x1, x2          // store in `x1` char* str which is in `x2`

    bl printf           // call printf

    ldr x0, [sp, 16]    // load into `x0` char* str

    bl free             // call free
                        // free allocated with calloc memory

    ldr lr, [sp, 24]    // return saved on stack value of `lr`
    add sp, sp, 32      // free allocated on stack memory
    
    ret


    .section .rodata
fmt_str:
    .string "%s"
append_str:
    .string ".suffix\0"
