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

- Up to this moment we have worked only with 32bit and 64bit values

- Let's see an example of working with 1 byte variables

```C
#include <inttypes.h>
#include <stdio.h>

char char_sum(char a, char b) {
    return a + b;
}

int main() {
    char first = 0;
    char second = 0;

    scanf("%c %c", &first, &second);

    char sum = char_sum(first, second);

    printf("sum of `%c` and `%c` equals to symbol `%c`\n", first, second, sum);
    printf("Or equals to number %" PRId8 "\n", sum);

    return 0;
}
```

- asm varinat

```
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
```