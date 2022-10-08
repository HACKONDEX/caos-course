# AArch64 assembly basics

- Let's consider more examples that are __not__ `C` code disassembly result

```С
#include <inttypes.h>
#include <stdio.h>
	
int main() {
	int32_t signed_value = 0;
	uint32_t unsigned_value = 0;
	
	scanf("%" PRId32, &signed_value);
	scanf("%" PRIu32, &unsigned_value);

	++signed_value;
	--unsigned_value;

	printf("signed value == %" PRId32 "\n", signed_value);
	printf("unsigned_value == %" PRIu32 "\n", unsigned_value);

	return 0;
}

```	

- ASM variant for code above

```
    .text
    .global main

main:
    sub sp, sp, 16              // allocate 16 bytes memory on stack(8 for `lr` value, 8 for two 32_bit integers)

    str lr, [sp, 8]             // store value of register lr on stack

    adr x0, format_str_signed   // store in `x0` char* for "%d"
    add x1, sp, 4               // store in `x1` pointer to int32_t allocated on stack

    bl scanf                    // call scanf

    adr x0, format_str_unsigned // store in `x0` char* for "%u"
    mov x1, sp                  // store in `x1` pointer to uint32_t allocated on stack

    bl scanf                    // call scanf

    ldr w2, [sp, 4]             // load into `w2` signed 32 bits from stack
    adds w2, w2, 1              // do signed increment(doesn't expect overflow)
    str w2, [sp, 4]             // store new value back to memory on stack

    adr x0, printf_fmt_signed   // store in `x0` char* for "signed value == %d\n"
    mov w1, w2                  // store in `w1` value of int32_t

    bl printf                   // call printf

    ldr w2, [sp]                // load into `w2` unsigned 32 bit from stack
    sub w2, w2, 1               // do signed decrement(supports overflow)
    str w2, [sp]                // store new value back to memory on stack

    adr x0, printf_fmt_unsigned // store in `x0` char* for "unsigned value == %u\n"
    mov w1, w2                  // store in `w1` value of uint32_t 

    bl printf                   // call printf

    ldr lr, [sp, 8]             // store in `lr` saved on stack old value of `lr`
    add sp, sp, 16              // free allocated space on stack

    mov x0, 0                   // store `0` in `x0`
    ret                         // return from main with value `0`


    .section .rodata
format_str_signed:
    .string "%d"
format_str_unsigned:
    .string "%u"
printf_fmt_signed:
    .string "signed value == %d\n"
printf_fmt_unsigned:
    .string "unsigned value == %u\n"

```