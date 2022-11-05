hellow_asm_seg:
	@ gcc -nostdlib -no-pie example_hello_world_segfault.S syscall.S -o hellow_asm_seg.exe

hellow_asm:
	@ gcc -nostdlib -no-pie example_hello_world.S syscall.S -o hellow_asm.exe

hellow_seg:
	@ gcc -nostdlib example_hello_world_segfault.c syscall.S -o hellow_seg.exe

hellow:
	@ gcc -nostdlib example_hello_world.c syscall.S -o hellow.exe

brk:
	@ gcc -m64 -masm=intel syscall.S brk.c -o brk.exe  

brk_nostdlib:
	@ gcc -m64 -masm=intel -nostdlib syscall.S brk_nostdlib.c -o brk_nostdlib.exe

clear:
	@ rm *.exe