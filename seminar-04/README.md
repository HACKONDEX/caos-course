# __ASM AArch64__

- If your computer's processor is not `ARM` architecture, you should install some additional tools for running binary code

 <font size="6"> 

### Note

- If you have problems with your linux, have MacBook with M1/M2 or  don't want to starve you can use [GodBolt](https://godbolt.org). Just choose there language _Assembly_ and _AArch64_ compiler.

## Install instructions

</font> 

1. Install aarch-64 gcc compiler

`sudo apt update && sudo apt upgrade`

`sudo apt --fix-broken install`

`sudo apt-get install gcc-aarch64-linux-gnu`

2. Install qemu-arm if haven't got already

`apt-get install qemu-system-arm`

`apt-get install qemu-efi-aarch64`

`apt-get install qemu-utils`

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

   .global	sum
   .global	sum3
   .global	mul
   .global	mul_add

sum:
	add	r0, r0, r1
	bx	lr

sum3:
	add	r0, r0, r1
	add	r0, r0, r2
	bx	lr

mul:
	mul	r0, r1, r0
	bx	lr

mul_add:
	mla	r0, r1, r0, r2
	bx	lr

```

## ARM calling convention

|_Registers_| _Function_ |_Value saved during call_|
|-----------|------------|-------------------------|
|__r0-r3__  |arguments/return values| __NO__|
|__r4-r11__ |local variables|__YES__|
|__r12(ip)__|intra-procedure-call scratch|__NO__|
|__r13(sp)__|stack pointer|__YES__|
|__r14(lr)__|link register|__NO__|
|__r15(pc)__|programme counter|__NO__|

- `pc` keeps the address of current running instruction
 
- `lr` holds the return address for a function call
 
- `sp` holds the address of current stack border

- First *4* arguments of function are in registers __r0-r3__, all other arguments are given through stack

- Function return value is in __r0__ or __r0-r1__

- Function call can't change values of registers __r4-r11__, so if you want to use them in your function, you should save them on stack before using

### How to write assembly programme

- Don't try to wrtie programm from clean slate, write some working `C` code, then look how it looks like on `ASM`

- Try to understand which instructions are essential and which are not necessary

#### Main instructions

- __`bx`__ branch and exchange `bx r$` **-** branch to the address contained in register `r$` and exchange the instruction set.

- __`mov`__ move `move r$, #1` **-** copies from second operand into first

- __`ldr`__ load `ldr r0, [r1]` **-** load into from variable by address in `r1`. `ldr r0, [r1, ]

- __`cmp`___ compare `cmp r0, r1` **-** compare `r0` and `r1` and set relevant flags

- __`add`__ add without carry `add r0, r1, r2` **-** count sum of `r1` and `r2`, save result in `r0`

- __`rsb`__ Reverse Subtract without carry `rsb r0, r1, r2` **-** subtracs `r1` from `r2` and save esult in `r0`

- __`mul`__ Multiply operands, giving the least significant 32 bits of the result `mul r0, r1, r2` **-** multiply `r1` and `r2`, save result in `r0`

- __`mla`__ multiply and add `mla r0, r1, r2, r3` **-** multiplye `r1` and `r2` then add `r3` and save result in `r0`


