integers: io_integers.c
	aarch64-linux-gnu-gcc io_integers.c -o io_integers.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./io_integers.exe

chars: char_sum.c
	aarch64-linux-gnu-gcc char_sum.c -o chars.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./chars.exe

memory: dynamic_memory.c
	aarch64-linux-gnu-gcc dynamic_memory.c -o mem.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./mem.exe


clear:
	rm -rf *.exe