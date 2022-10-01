	.arch armv8-a
	.file	"compare.c"
	.text
	.align	2
	.global	func
	.type	func, %function
func:
.LFB0:
	.cfi_startproc
	cmp	x0, x1
	bge	.L2
	add	x0, x1, 7
.L1:
	ret
.L2:
	add	x2, x1, 1
	add	x1, x0, x1
	cmp	x2, x0
	mov	x0, 21
	csel	x0, x1, x0, ne
	b	.L1
	.cfi_endproc
.LFE0:
	.size	func, .-func
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
