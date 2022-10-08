    .arch armv8-a
    .text
    .global char_sum
    .global main

char_sum:
    adds w0, w0, w1      // store in `w0` sum of signed numbers
    ret

main:
    sub sp, sp, 16       // allocate 16 bytes on stack
    str lr, [sp, 8]      // save on stack value of `lr`

    adr x0, scanf_fmt    // load into `x0` char* "scanf_fmt"
    add x1, sp, 7        // store in `x1` address of the 9th allocated byte
    add x2, sp, 6        // store in `x2` address of the 10th allocated byte

    bl scanf             // call scanf

    ldrsb x0, [sp, 7]    // load into `x0` first char(which we read)
    ldrsb x1, [sp, 6]    // load into `x1` second char(which we also read)

    bl char_sum          // call char_sum

    strb w0, [sp, 5]     // put value returned by `char_sum` on stack

    mov w3, w0           // copy into `w3` value from `w0`
    adr x0, printf_fmt_1 // load into `x0` char*
    ldrsb w1, [sp, 7]    // load into `w1` 1 signed byte from address [sp + 7]
    ldrsb w2, [sp, 6]    // load into `w2` 1 signed byte from address [sp + 6]

    bl printf            // call printf

    ldrsb w1, [sp, 5]    // load into `w1` 1 signed byte from address [sp + 5]
    adr x0, printf_fmt_2 // load into `x0` address of string (char *)

    bl printf            // call printf

    ldr lr, [sp, 8]      // load into `lr` its old value, which we saved on stack at the begging
    add sp, sp, 16       // free allocated on stack memory
    mov x0, 0            // main returns 0
    ret


    .section .rodata
scanf_fmt:
    .string "%c %c"
printf_fmt_1:
    .string "sum of `%c` and `%c` equals to symbol `%c`\n"
printf_fmt_2:
    .string "Or equals to number %d\n"



    
