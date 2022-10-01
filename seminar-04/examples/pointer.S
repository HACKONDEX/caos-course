	.arch armv8-a
	.file	"pointer.c"
	.text
	.align	2
	.global	compare_and_exchange
	.type	compare_and_exchange, %function
compare_and_exchange:
.LFB0:
	.cfi_startproc
	ldr	x3, [x0]
	ldr	x4, [x1]
	cmp	x3, x4
	bne	.L2
	str	x2, [x0]
	mov	w0, 1
.L3:
	ret
.L2:
	mov	w0, 0
	str	x3, [x1]
	b	.L3
	.cfi_endproc
.LFE0:
	.size	compare_and_exchange, .-compare_and_exchange
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
