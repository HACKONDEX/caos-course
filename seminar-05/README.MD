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

- asm varinat the code above

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

- Example of using heap memory(dynamic allocation)

```C
#include <inttypes.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>


int main() {
    char* str = calloc(50, sizeof(char));
    scanf("%s", str);

    uint32_t len = 0;
    for (uint32_t i = 0; str[i] != '\0' ; ++i) {
        ++len;
    }

    char* append_str = "Appended";
    uint32_t append_len = strlen(append_str);
    for (uint32_t i = len; i < len + append_len; ++i) {
        str[i] = append_str[i - len];
    }

    printf("%s", str);
    
    free(str);
    return 0;
}
```

__-__ The same code on asm with detailed comments

```
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
```