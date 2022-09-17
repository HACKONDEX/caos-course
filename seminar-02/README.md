<div class="cell markdown">

# C, GCC, Makefile, GDB

  - `C` is a compiled language, its programm file must have `.c`
    extension
  - There are many `C` compilers, most popular ones for linux are 1) GCC
    2) Clang
  - In our course we will use `GCC`

</div>

<div class="cell code" data-execution_count="34">

``` python
%%file hello_world.c

#include <stdio.h>

int main() {
    printf("Hello world!\n");
    return 0;
}
```

<div class="output stream stdout">

    Overwriting hello_world.c

</div>

</div>

<div class="cell markdown">

  - `-o` option is for giving name to the generated executable. If not
    used, binary file has name `a.out`.

</div>

<div class="cell code" data-execution_count="35">

``` python
!gcc hello_world.c -o hello_world.exe
!./hello_world.exe
```

<div class="output stream stdout">

    Hello world!

</div>

</div>

<div class="cell markdown">

## Compilation

  - `C` programm compilation consists of **4** main parts

-----

1\) Pre-processing **:** comments removal, file inclusion, macros
expansion, conditional compilation

2\) Compilation **:** convertion into assembly code

3\) Assembling **:** convertion into a machine-understandable code

## 4\) Linking **:** generates an executable file

  - [Small article about
    compilation](https://www.scaler.com/topics/c/compilation-process-in-c/)

</div>

<div class="cell markdown">

### Pre-processing example

  - Comments will be removed as they are not of particular use for the
    machine.

  - File inclusion will cause the entire content of `header` to be added
    into the source code, replacing the `#include<header>`.

  - Compile-time known constants, values or expressions defined using
    `#define` directive are replaced.

  - ## Replace conditional cmpilation directives `#ifdef`, `#endif` with real codes.

  - `-E` option for generating file right after **pre-process** step.

</div>

<div class="cell code" data-execution_count="36">

``` python
%%file preprocess_example.h
#define ERROR_CODE -1
#define SUCCESS_CODE 0

int convert_euros_to_rubles(int* amount) {
    if (*amount > 0) {
        *amount *= 60;
        return SUCCESS_CODE;
    }
    return ERROR_CODE;
}
```

<div class="output stream stdout">

    Overwriting preprocess_example.h

</div>

</div>

<div class="cell code" data-execution_count="37">

``` python
%%file preprocess_example.c
#include "preprocess_example.h"

#define OPTION_1 1

// Some magic counting
int count() {
    int amount = 0;
    
    #ifdef OPTION_1
        amount = 33;
    #else
        amount = 77;
    #endif

    if (convert_euros_to_rubles(&amount) == 0) {
        return amount;
    }
    return ERROR_CODE;
}
```

<div class="output stream stdout">

    Overwriting preprocess_example.c

</div>

</div>

<div class="cell code" data-execution_count="38">

``` python
!gcc -E preprocess_example.c -o preprocess_example_E.c
```

</div>

<div class="cell markdown">

#### Code after prep-rocess step

``` c
# 0 "preprocess_example.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "preprocess_example.c"
# 1 "preprocess_example.h" 1



int convert_euros_to_rubles(int* amount) {
    if (*amount > 0) {
        *amount *= 60;
        return 0;
    }
    return -1;
}
# 2 "preprocess_example.c" 2




int count() {
    int amount = 0;


        amount = 33;




    if (convert_euros_to_rubles(&amount) == 0) {
        return amount;
    }
    return -1;
}
```

</div>

<div class="cell markdown">

### Compilation

</div>

<div class="cell markdown">

  - Takes the output of the pre-processor and generates assembly
    language.

  - It is an intermediate human readable language, **specific to the
    target processor** .

  - ## Assembly file must have `.S` extension.

  - `-S` option for generating file right after **compilation** step.

</div>

<div class="cell code" data-execution_count="39">

``` python
%%file asm_example.c
#include <limits.h>
#include <stdio.h>

unsigned int get_remains(unsigned int x, unsigned int y) {
    return x % y;
}

unsigned int sum(unsigned int x, unsigned int y) {
    if (x + y < x) {
        return UINT_MAX;
    }
    return x + y;
}

int main() {
    unsigned int x = 13;
    unsigned int y = 20;

    printf("The remainder of %u devided by %u is %u \n", x, y, get_remains(x, y));

    printf("Sum of %u and %u is %u \n", x, y, sum(x, y));

    printf("Sum of %u and 1 is %u which is the UINT_MAX \n", UINT_MAX, sum(1, UINT_MAX));

    return 0;
}
```

<div class="output stream stdout">

    Overwriting asm_example.c

</div>

</div>

<div class="cell markdown">

  - Let's compile and look at first 20 and last 10 lines of assembly
    code

</div>

<div class="cell code" data-execution_count="40">

``` python
!gcc -S asm_example.c -o asm_example_S.S
!head -n 20 asm_example_S.S
```

<div class="output stream stdout">

``` 
	.file	"asm_example.c"
	.text
	.globl	get_remains
	.type	get_remains, @function
get_remains:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	movl	$0, %edx
	divl	-8(%rbp)
	movl	%edx, %eax
	popq	%rbp
```

</div>

</div>

<div class="cell code" data-execution_count="41">

``` python
!tail -n 10 asm_example_S.S
```

<div class="output stream stdout">

``` 
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
```

</div>

</div>

<div class="cell markdown">

  - Let's compile the file generated right after pre-process step.

</div>

<div class="cell code" data-execution_count="42">

``` python
!gcc -S -O1 preprocess_example_E.c -o preprocess_example_S.S
```

</div>

<div class="cell markdown">

  - `-O1` option stands for getting more compact and readable assembly
    file.
  - We get valid assembly programm.

<!-- end list -->

``` asm
	.file	"preprocess_example_E.c"
	.text
	.globl	convert_euros_to_rubles
	.type	convert_euros_to_rubles, @function
convert_euros_to_rubles:
.LFB0:
	.cfi_startproc
	endbr64
	movl	(%rdi), %eax
	testl	%eax, %eax
	jle	.L3
	imull	$60, %eax, %eax
	movl	%eax, (%rdi)
	movl	$0, %eax
	ret
.L3:
	movl	$-1, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	convert_euros_to_rubles, .-convert_euros_to_rubles
	.globl	count
	.type	count, @function
count:
.LFB1:
	.cfi_startproc
	endbr64
	movl	$1980, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	count, .-count
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
```

</div>

<div class="cell markdown">

### Assembling

  - Just generates from assembly code machine code file.

  - It is not readable for humans.

  - `-c` option generates machine code file and stops, **Linking** step
    doesn't happen.

</div>

<div class="cell code" data-execution_count="43">

``` python
!gcc -c hello_world.c -o hello_world.obj
!cat hello_world.obj
```

<div class="output stream stdout">

``` 
```

</div>

</div>

<div class="cell markdown">

  - `hello_world.obj` file is a machine code file, it is not readable in
    raw format as other files

  - You can use `readelf -WaS` terminal command to get better picture.

</div>

<div class="cell code" data-execution_count="44">

``` python
!readelf -WaS hello_world.obj
```

<div class="output stream stdout">

    ELF Header:
      Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
      Class:                             ELF64
      Data:                              2's complement, little endian
      Version:                           1 (current)
      OS/ABI:                            UNIX - System V
      ABI Version:                       0
      Type:                              REL (Relocatable file)
      Machine:                           Advanced Micro Devices X86-64
      Version:                           0x1
      Entry point address:               0x0
      Start of program headers:          0 (bytes into file)
      Start of section headers:          608 (bytes into file)
      Flags:                             0x0
      Size of this header:               64 (bytes)
      Size of program headers:           0 (bytes)
      Number of program headers:         0
      Size of section headers:           64 (bytes)
      Number of section headers:         14
      Section header string table index: 13
    
    Section Headers:
      [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
      [ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
      [ 1] .text             PROGBITS        0000000000000000 000040 00001e 00  AX  0   0  1
      [ 2] .rela.text        RELA            0000000000000000 0001a0 000030 18   I 11   1  8
      [ 3] .data             PROGBITS        0000000000000000 00005e 000000 00  WA  0   0  1
      [ 4] .bss              NOBITS          0000000000000000 00005e 000000 00  WA  0   0  1
      [ 5] .rodata           PROGBITS        0000000000000000 00005e 00000d 00   A  0   0  1
      [ 6] .comment          PROGBITS        0000000000000000 00006b 000027 01  MS  0   0  1
      [ 7] .note.GNU-stack   PROGBITS        0000000000000000 000092 000000 00      0   0  1
      [ 8] .note.gnu.property NOTE            0000000000000000 000098 000020 00   A  0   0  8
      [ 9] .eh_frame         PROGBITS        0000000000000000 0000b8 000038 00   A  0   0  8
      [10] .rela.eh_frame    RELA            0000000000000000 0001d0 000018 18   I 11   9  8
      [11] .symtab           SYMTAB          0000000000000000 0000f0 000090 18     12   4  8
      [12] .strtab           STRTAB          0000000000000000 000180 000019 00      0   0  1
      [13] .shstrtab         STRTAB          0000000000000000 0001e8 000074 00      0   0  1
    Key to Flags:
      W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
      L (link order), O (extra OS processing required), G (group), T (TLS),
      C (compressed), x (unknown), o (OS specific), E (exclude),
      D (mbind), l (large), p (processor specific)
    
    There are no section groups in this file.
    
    There are no program headers in this file.
    
    There is no dynamic section in this file.
    
    Relocation section '.rela.text' at offset 0x1a0 contains 2 entries:
        Offset             Info             Type               Symbol's Value  Symbol's Name + Addend
    000000000000000b  0000000300000002 R_X86_64_PC32          0000000000000000 .rodata - 4
    0000000000000013  0000000500000004 R_X86_64_PLT32         0000000000000000 puts - 4
    
    Relocation section '.rela.eh_frame' at offset 0x1d0 contains 1 entry:
        Offset             Info             Type               Symbol's Value  Symbol's Name + Addend
    0000000000000020  0000000200000002 R_X86_64_PC32          0000000000000000 .text + 0
    No processor specific unwind information to decode
    
    Symbol table '.symtab' contains 6 entries:
       Num:    Value          Size Type    Bind   Vis      Ndx Name
         0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
         1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS hello_world.c
         2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 .text
         3: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 .rodata
         4: 0000000000000000    30 FUNC    GLOBAL DEFAULT    1 main
         5: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND puts
    
    No version information found in this file.
    
    Displaying notes found in: .note.gnu.property
      Owner                Data size 	Description
      GNU                  0x00000010	NT_GNU_PROPERTY_TYPE_0	      Properties: x86 feature: IBT, SHSTK

</div>

</div>

<div class="cell markdown">

### Linking

</div>

<div class="cell markdown">

  - The linking process generates an executable file.

  - Includes library files to the programm.

  - After linking the operating system uderstands where to look for
    library funtions, variables, etc.

  - Linking process automatically takes place after **assembling**.

  - `gcc` can build executable from simultaneously `.c` file `.S` and
    '.obj\` files.

  - You can link your source code file with `.obj` file from some
    library, and the linker will find the functions you use in your code
    in the library `.obj` file.

-----

#### Example

</div>

<div class="cell code" data-execution_count="1">

``` python
%%file gcd.h

int gcd(int x, int y);
```

<div class="output stream stdout">

    Writing gcd.h

</div>

</div>

<div class="cell code" data-execution_count="2">

``` python
%%file gcd.c
#include "gcd.h"

int gcd(int x, int y) {
    while (x != y) {
        if (x > y) {
            x -= y;
        } else {
            y -= x;
        }
    }
    
    return x;
}
```

<div class="output stream stdout">

    Writing gcd.c

</div>

</div>

<div class="cell code" data-execution_count="5">

``` python
%%file calculate_gcd.c
#include "gcd.h"
#include <stdio.h>

int main() {
    printf("GCD of %d and %d equals %d", 21, 77, gcd(21, 77));
    return 0;
}
```

<div class="output stream stdout">

    Overwriting calculate_gcd.c

</div>

</div>

<div class="cell code" data-execution_count="6">

``` python
!gcc -c gcd.c -o gcd.obj
!gcc calculate_gcd.c gcd.obj -o gcd.exe
!./gcd.exe
```

<div class="output stream stdout">

    GCD of 21 and 77 equals 7

</div>

</div>

<div class="cell markdown">

  - **Note** that you need exactly one `main` function in one of the
    files, if you have less or more and compile without special options,
    `gcc` will fail with error.

</div>

<div class="cell markdown">

### Options

  - `-o` option for giving name to the final generated file.

  - `-std` option is for setting standart of `C` language.

  - `-Wall` option enables all compiler's warning messages.

  - `-Werror` option make all warning mesages into error messages.

  - `Wfatal-errors` option causes the compiler to abort compilation on
    the first error.

  - `-E` option to generate `.c` or `.i` file which will include the
    content of the source code right after pre-process step.

  - `-S` option to generate `.S` assembly file of the source code.

  - `-c` option to generate `.o` or `.obj` machine-code file withour
    linking step.

  - `-g` option for debugging with **gdb**.

  - `-D` option defines macro to be used during pre-process step.

</div>

<div class="cell markdown">

#### Example

</div>

<div class="cell code" data-execution_count="15">

``` python
%%file option.c
#include <stdio.h>

int main() {
    printf("TEXT is not defined in programm but TEXT == %s", TEXT);
    return 0;
}
```

<div class="output stream stdout">

    Overwriting option.c

</div>

</div>

<div class="cell code" data-execution_count="16">

``` python
!gcc option.c -DTEXT="\"Hey from shell\"" -o option.exe
!./option.exe
```

<div class="output stream stdout">

    TEXT is not defined in programm but TEXT == Hey from shell

</div>

</div>

<div class="cell markdown">

  - There are lots of additional options, you can find them
    [here](https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html).

</div>

<div class="cell markdown">

### Makefile

  - **Makefile** is used by `make` utility to update, run, compile,
    delete files and more.

  - To use utility `make` you need to install it and write a file, which
    must strictly have name `Makefile`.

  - in `Makefile` we have **targets** and **dependencies**

Here is a template view of **Makefile**

``` make
    target1: <prerequisites>
    <TAB> recipe
    target2: ...
```

To run a target we just run in shell `make target_name`. If you have
target called `all` in **Makefile** it will run in case of using just
`make` command

  - Note that in both cases Makefile is in the same directory where we
    run `make` command.

#### Example

``` makefile
say_hello:
    gcc hello_world.c -o hello_world.exe
    ./hello_world.exe
clear:
    rm -f hello_world.exe
```

</div>

<div class="cell code" data-execution_count="27">

``` python
!make say_hello
```

<div class="output stream stdout">

    gcc hello_world.c -o hello_world.exe
    ./hello_world.exe
    Hello world!

</div>

</div>

<div class="cell code" data-execution_count="28">

``` python
!make clear
!ls | grep "hello_world.exe"
```

<div class="output stream stdout">

    rm -f hello_world.exe > /dev/null

</div>

</div>

<div class="cell markdown">

</div>

<div class="cell markdown">

</div>
