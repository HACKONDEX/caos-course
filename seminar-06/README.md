# __ASM x86-64__

- x86-64 is another processor architecture

- Assembly code for this architecture has two syntaxes `AT&T` and `intel`, we will use `intel` syntax

## Compilation and execution

- on linux use default gcc compiler with flags 

- Disassembly example

      gcc -m64 -masm=intel -S -O3 code.c -o code.S

- One compilation unit

      gcc -m64 -masm=intel disasom_example.S -o run.exe

- Many compilation units

      gcc -m64 -masm=intel disasom_exmaple.S main.c -o run.exe

- You don't need emulator for running if your processor mark is `intel` or `amd`

      ./run.exe

---------------------------

### <center>__x86-64__ registers</center>

- Has `16 general purpose registers` and `8 large registers` for floating point numbers operations

- `rax`, `rbx`, `rcx`, `rdx`, `rsi`, `rdi` __-__ general purpose, for any operations

- `rsp` __-__ stack pointer

- `rbp` __-__ pointer to the begging of the stack frame

- `r8-r15` __-__ more registers

- `xmm0-xmm7` __-__ floating point registers

-----------------

- General arguments functions receive in registers `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9` in the given order

- If function expects more than `6` arguments, they should be sotred on stack

- Function __return value__ is stored in register `rax`

- ___Note___ that rules above don't apply to floating point types(will discuss it on next lesson)

- __Callee__ function must save values of registers `rbx`, `rbp`, `r12-r15`

-----------------

- __Stack__ must always be aligned with ___16___ bytes


