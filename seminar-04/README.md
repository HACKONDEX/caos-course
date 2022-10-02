# __ASM AArch64__


- If your computer's processor is not `ARM` architecture, you should install some additional tools for running binary code

 <font size="6"> 

### Note

- If you have problems with your linux, have MacBook with M1/M2 or  don't want to starve you can use [GodBolt](https://godbolt.org). Just choose there language _Assembly_ and _AArch64_ compiler.

- Also read [Yakovlev's reading](https://github.com/victor-yacovlev/fpmi-caos/tree/master/practice/aarch64) for better understanding

## Install instructions

</font> 

1. Install aarch-64 gcc compiler

----
      sudo apt update && sudo apt upgrade
----
      sudo apt --fix-broken install
----
      sudo apt-get install gcc-aarch64-linux-gnu
----

2. Install qemu-arm if haven't got already

----
      apt-get install qemu-system-arm
----
      apt-get install qemu-efi-aarch64
----
      apt-get install qemu-utils

3. If you have problems with compilation and execution, just search in google the error message. You will find solution for your problem in *99%* of cases.

## Compile and run

1. Compile examples
   
   - `aarch64-linux-gnu-gcc main.c -o programme.exe`
   - `aarch64-linux-gnu-gcc main.S -o programme.exe`
   - `aarch64-linux-gnu-gcc main.c lib.S -o programme.exe` 
   - `aarch64-linux-gnu-gcc -S -O3 lib.c -o lib.S`

2. Execute examples
   
   - `qemu-aarch64 -L /usr/aarch64-linux-gnu ./programme.exe`

   - You can set environment variable, and use without giving path to the shared libs

   - `export QEMU_LD_PREFIX=/usr/aarch64-linux-gnu`
  
   - `qemu-aarch64 ./programme.exe`


## Assembly code

- Get assembly code of your programme on `C` with option `-S`
  
`aarch64-linux-gnu-gcc -S example.c -o example.S`

- Use option `-Os` for getting more readable asm code

`aarch64-linux-gnu-gcc -S -Os example.c -o example.S`

- Or, if you already have object file of your code

`aarch64-linux-gnu-gcc -c -Os example.c -o example.o`

- Then, just look at its objdump
  
`aarch64-linux-gnu-objdump -D example.o`

- Example

```C
%file example.c

int sum(int x, int y) {
	return x + y;
}

int sum3(int a, int b, int c) {
	return a + b + c;
}

int mul(int x, int y) {
	return x * y;
}

int mul_add(int a, int b, int c) {
	return a * b + c;
}
```

- Of course, after compiling into asm code, we will have a lot of additional instructions and code lines, as it is created by machine. Here you can see the most significant parts

```ASM
   .text
   .global	sum
   .global	sum3
   .global	mul
   .global	mul_add

sum:
	add	w0, w0, w1
	ret

sum3:
	add	w0, w0, w1
	add	w0, w0, w2
	ret

mul:
	mul	w0, w0, w1
	ret

mul_add:
	madd	w0, w0, w1, w2
	ret


```

## Calling convention


### <center>AArch64(armv8(arm64))</center>

<center>

|_Registers_| _Function_ |_Value saved during call_|
|-----------|------------|-------------------------|
|__x0-x7__  |arguments/return values| __NO__|
|__x8-x15__ |local variables, scratch registers|__NO__|
|__x16-x17__|intra-procedure-call scratch|__NO__|
|__x18__|platform register|__NO__|
|__x19-x28__|scratch registers|__YES__|
|__x29(fp)__|frame pointer|__YES__|
|__x30(lr)__|procedure link register|__YES__|
|__sp__|stack pointer|__NO__|
|__pc__|programm counter|__NO__|

</center>

- We can use __lower 32 bits__ of the registers `x0-x30` operating with `w0-w30`, don't forget that in case you use `w$` the __significant 32 bits__ of `w$` can contain any value

- `pc` keeps the address of current running instruction, isn't indexed register, has limited access 
 
- `lr` holds the return address for a function call
 
- `sp` holds the address of current stack border, isn't indexed register, has limited access
  
- `fp` required for compatibility with fast stack walking

- First *8* arguments of function are in registers __x0-x7__, all other arguments are given through stack

- Function return value is in __x0__ or __x0-x1__

- Function call can't change values of registers __x19-x28__, so if you want to use them in your funtion, you should save them on stack before using


      You can compare arm32 with aarch64

---------------------------------------

### <center>Arm 32</center>

<center>

|_Registers_| _Function_ |_Value saved during call_|
|-----------|------------|-------------------------|
|__r0-r3__  |arguments/return values| __NO__|
|__r4-r11__ |local variables|__YES__|
|__r12(ip)__|intra-procedure-call scratch|__NO__|
|__r13(sp)__|stack pointer|__YES__|
|__r14(lr)__|link register|__NO__|
|__r15(pc)__|programme counter|__NO__|

</center>

- `pc` keeps the address of current running instruction
 
- `lr` holds the return address for a function call
 
- `sp` holds the address of current stack border

- First *4* arguments of function are in registers __r0-r3__, all other arguments are given through stack

- Function return value is in __r0__ or __r0-r1__

- Function call can't change values of registers __r4-r11__, so if you want to use them in your function, you should save them on stack before using

---------------------------------------

### How to write assembly programme

- Don't try to wrtie programm from clean slate, write some working `C` code, then look how it looks like on `ASM`

- Try to understand which instructions are essential and which are not necessary

#### Main instructions

You can find all general instructions [__here__](https://developer.arm.com/documentation/dui0802/b/A64-General-Instructions/A64-general-instructions-in-alphabetical-order?lang=en)

- __`b`__ branch by label `b Label` **-** branch to the address of `Label`

- __`bl`__ branch by label `bl Label` **-** branch to the address of `Label`, and save the address right after `bl Lable` in `lr` register, to be able to return using instruction `ret`

- __`br` branch by address `br x$` **-** branch to the address contained in register `x$`

- __`brl` branch by address `brl x$` **-** branch to the address contained in register `x$`, and save the address right after `brl x$` in `lr` register, to be able to return using instruction `ret`

- __`mov`__ move `move x$, #1` **-** copies from second operand into first

- __`add`__ add without carry `add x0, x1, x2` **-** counts sum of `x1` and `x2`, save result in `x0`

- __`sub`__ sub without carry `sub x0, x1, x2` **-** subtracts `x2` from `x1` and saves result in `x0`

- __`mul`__ Multiply operands, giving the least significant 32 bits of the result `mul x0, x1, x2` **-** multiply `x1` and `x2`, save result in `x0`

- __`cmp`___ compare `cmp x0, x1` **-** compare `x0` and `x1` and set relevant flags

#### Check presence of flag using suffixes

- __`eq`__ **-** equal

- __`ne`__ **-** not equal

- __`ge`__ **-** greater than or equal

- __`le`__ **-** less than or equal

- __`gt`__ **-** greater than

- __`lt`__ **-** less than

##### Compare and branching example

```C
%file compare.c

long long func(long long x, long long y) {
    if (x < y) {
        return y + 7;;
    }
    if (x == y + 1) {
        return 21;
    }
    return x + y;
}
```
      aarch64-linux-gnu-gcc -S -Os compare.c -o compare.S

```

	.text
	.global	func
func:
	cmp	x0, x1
	bge	.L2
	add	x0, x1, 7

.L1:
	ret

.L2:
	add	x2, x1, 1
	add	x1, x0, x1
	cmp	x2, x0
	mov	x0, 21
	csel	x0, x1, x0, ne
	b	.L1

```

- __`ldr`__ load `ldr x0, [x1]` **-** load into from variable by address in `x1`

- __`str`__ save `str x0, [x1]` **-** save data from register `x0` in memory cell with address in register `x1`

- __`adr`__ from relative address `adr x0, label` stores in register `x0` address of the `label`

#### Pointers and addresses example

```C
%file pointer.c

#include <inttypes.h>

char compare_and_exchange(int64_t* contained, int64_t* expected, int64_t value) {
    if (*contained == *expected) {
        *contained = value;
        return 1;
    }
    *expected = *contained;
    return 0;
}
```

      aarch64-linux-gnu-gcc -S -Os pointer.c -o pointer.S

```
	.text
	.global	compare_and_exchange
compare_and_exchange:
	ldr	x3, [x0]
	ldr	x4, [x1]
	cmp	x3, x4
	bne	.L2
	str	x2, [x0]
	mov	w0, 1

.L3:
	ret

.L2:
	mov	w0, 0
	str	x3, [x1]
	b	.L3
```
-----------------------

## How to call a function in asm

- As we already understood, to make a function we just write our code and put a label with the name of funtion at the beginnning of function

- Last instruction of the funtion must be `ret`

- To call a function we use `bl` instruction, as we alrdeady have label `func_name`, we just call using `bl func_name`

- Before calling the function, we should store in registers `x0-x7` values of the arguments 

- Also as `bl` changes value in register `lr` we must save its value on stack, and return the value from stack into register after function called

### Example

```C
%file func_call.c

#include <inttypes.h>
#include <stdio.h>

int64_t get_int64() {
    int64_t var = 0;
    scanf("%ld", &var);
    return var;
}
```

- Let's wrtie asm variant of this code

```

	.text
	.global get          // define global function get

get:
	sub sp, sp, 16       // allocate 16 bytes memory on stack(remeber about stack alignment 16)

	str lr, [sp, 8]      // store value of register lr on stack

	adr x0, format_str   // store char* in x0, as first argument of scanf is char*

	mov x1, sp           // second argument should be int64_t*, as we already used
                         // first 8 allocated on stack, rest 8 bytes we will use for int64_t
	bl scanf             // call scanf

	ldr x0, [sp]         // scanf read value from stdin into 8 bytes on stack
                         // we load it into x0, as return value must be in x0 
	ldr lr, [sp, 8]      // we store saved on stack old value of register lr
	add sp, sp, 16       // free allocated space on stack
	ret

	.section .rodata     // section .rodata
format_str:
	.string "%ld"        // in final binary will be these chars in the same order

```


