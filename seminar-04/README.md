# __ASM ARM__

- If your computer's processor is not `ARM` architecture, you should install some additional tools for running binary code

 <font size="6"> 

### Note

- If you have problems with your linux, have MacBook with M1/M2 or  don't want to starve you can use [GodBolt](https://godbolt.org). Just choose there language _Assembly_ and _ARM gcc_ compiler.

## Install instructions

</font> 

1. Download compilers and dynamic libraries

`wget http://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/arm-linux-gnueabi/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabi.tar.xz`

2. Unpack downloaded file

`tar xvf gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabi.tar.xz`

3. Install qemu-arm if haven't got already

`sudo apt-get install qemu-user-static qemu-system-arm qemu-user`

4. In case it doesn't work  

`sudo apt update && sudo apt upgrade`

`sudo apt-get install zlib1g:i386`

`sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386`

`sudo dpkg --add-architecture i386`

1. If you have other problems, just search in google the error message. You will find solution for your problem in *99%* of cases.

## Compile and run

1. Add paths to the compilers

`export PATH=$PATH:<local path to directory with unpacked linaro>/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabi/bin`

2. Add paths to the shared-libs for emulator

`export QEMU_LD_PREFIX=<local path to directory with unpacked linaro>/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabi/arm-linux-gnueabi/libc`

3. Compile and run examples
   
   - arm-linux-gnueabi-gcc -marm main.c -o programm.exe
   - arm-linux-gnueabi-gcc -marm main.S -o programm.exe 
   - arm-linux-gnueabi-gcc -marm main.c lib.S -o programm.exe 
   - arm-linux-gnueabi-gcc -marm -S -O3 lib.c -o lib.S

   - qemu-arm ./program.exe

## Assembly code

- Get assembly code of your programme on `C` with option `-S`
  
`arm-linux-gnueabi-gcc -S -marm example.c -o example.S`

- Use option `-Os` for getting more readable asm code

`arm-linux-gnueabi-gcc -S -Os -marm example.c -o example.S`

- Or, if you already have object file of your code

`arm-linux-gnueabi-gcc -c -Os -marm example.c -o example.o`

- Then, just look at its objdump
  
`arm-linux-gnueabi-objdump -D example.o`

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