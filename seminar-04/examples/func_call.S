	.text
	.global get          // define global function get

get:
	sub sp, sp, 16       // allocate 16 bytes memory on stack(remeber about stack alignment 16)

	str lr, [sp, 8]      // store value of register lr on stack

	adr x0, format_str   // store char* in x0, as first argument of scanf is char*

	mov x1, sp           // second argument should be int64_t*, as we already used
                         // first 8 allocated on stack, rest 8 bytes we will use for int64_t
	bl scanf             // call scanf

	ldr x0, [sp]         // scanf read value from stdin into 8 bytes on stack
                         // we load it into x0, as return value must be in x0 
	ldr lr, [sp, 8]      // we return saved value of register lr
	add sp, sp, 16       // free allocated space on stack
	ret

	.section .rodata     // section .rodata
format_str:
	.string "%ld"        // in final binary will be these char in same order
