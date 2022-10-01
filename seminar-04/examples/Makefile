compare:
	aarch64-linux-gnu-gcc -S -Os compare.c -o compare.S

pointer:
	aarch64-linux-gnu-gcc -S -Os pointer.c -o pointer.S

test:
	aarch64-linux-gnu-gcc test.c -o test.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./test.exe

hello:
	aarch64-linux-gnu-gcc hello.c -o hello.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./hello.exe

clear:
	rm -rf *.exe