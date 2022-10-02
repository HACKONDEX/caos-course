solution_1:
	aarch64-linux-gnu-gcc main.c variant_1.S -o var1.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./var1.exe

solution_2:
	aarch64-linux-gnu-gcc main.c variant_2.S -o var2.exe
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./var2.exe

clear:
	rm -rf *.exe
