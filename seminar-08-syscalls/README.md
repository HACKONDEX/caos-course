# Linux System calls, `C` without libc

__Syscall__ __-__ is a userspace request of a kernel service. The syscall in our programm causes processor interruption and then the kernel handls the interrupt executing some code from kernel.

Syscall gives the programm ability to interact with the operating system and request some resources. For example sockets, physical-memory, connections to other hardware components like audio-card, battery, net-card and etc.

### Useful links

[Yakovlev's reading](https://github.com/victor-yacovlev/fpmi-caos/tree/master/practice/asm/nostdlib_baremetal)

[Articles about intteruption](https://0xax.gitbooks.io/linux-insides/content/Interrupts/index.html)

[System calls more theory](https://0xax.gitbooks.io/linux-insides/content/SysCall/linux-syscall-1.html)

