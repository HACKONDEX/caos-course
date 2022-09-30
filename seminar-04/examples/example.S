	.arch armv8-a
	.file	"example.c"
	.text
	.align	2
	.global	sum
	.type	sum, %function
sum:
.LFB0:
	.cfi_startproc
	add	w0, w0, w1
	ret
	.cfi_endproc
.LFE0:
	.size	sum, .-sum
	.align	2
	.global	sum3
	.type	sum3, %function
sum3:
.LFB1:
	.cfi_startproc
	add	w0, w0, w1
	add	w0, w0, w2
	ret
	.cfi_endproc
.LFE1:
	.size	sum3, .-sum3
	.align	2
	.global	mul
	.type	mul, %function
mul:
.LFB2:
	.cfi_startproc
	mul	w0, w0, w1
	ret
	.cfi_endproc
.LFE2:
	.size	mul, .-mul
	.align	2
	.global	mul_add
	.type	mul_add, %function
mul_add:
.LFB3:
	.cfi_startproc
	madd	w0, w0, w1, w2
	ret
	.cfi_endproc
.LFE3:
	.size	mul_add, .-mul_add
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
