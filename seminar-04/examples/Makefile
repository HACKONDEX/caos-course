compare:
	aarch64-linux-gnu-gcc -S -Os compare.c -o compare.S

pointer:
	aarch64-linux-gnu-gcc -S -Os pointer.c -o pointer.S

align:
	aarch64-linux-gnu-gcc align.c -o align.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./align.exe

hello:
	aarch64-linux-gnu-gcc hello.c -o hello.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./hello.exe

clear:
	rm -rf *.exe