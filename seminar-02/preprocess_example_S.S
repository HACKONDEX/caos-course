	.file	"preprocess_example_E.c"
	.text
	.globl	convert_euros_to_rubles
	.type	convert_euros_to_rubles, @function
convert_euros_to_rubles:
.LFB0:
	.cfi_startproc
	endbr64
	movl	(%rdi), %eax
	testl	%eax, %eax
	jle	.L3
	imull	$60, %eax, %eax
	movl	%eax, (%rdi)
	movl	$0, %eax
	ret
.L3:
	movl	$-1, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	convert_euros_to_rubles, .-convert_euros_to_rubles
	.globl	count
	.type	count, @function
count:
.LFB1:
	.cfi_startproc
	endbr64
	movl	$1980, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	count, .-count
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
