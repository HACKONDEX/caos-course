integers: io_integers.c
	aarch64-linux-gnu-gcc io_integers.c -o io_integers.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./io_integers.exe

chars: char_sum.c
	aarch64-linux-gnu-gcc char_sum.c -o chars.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./chars.exe

clear:
	rm -rf *.exe