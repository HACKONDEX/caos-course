	.file	"inf6-0.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	very_important_function
	.type	very_important_function, @function
very_important_function:
.LFB23:
	.cfi_startproc
	endbr64
	test	rdi, rdi
	je	.L4
	xor	eax, eax
	vxorpd	xmm0, xmm0, xmm0
	.p2align 4,,10
	.p2align 3
.L3:
	vmovss	xmm1, DWORD PTR [rsi+rax*4]
	vaddss	xmm1, xmm1, DWORD PTR [rdx+rax*4]
	vmovss	DWORD PTR [rcx+rax*4], xmm1
	add	rax, 1
	vcvtss2sd	xmm1, xmm1, xmm1
	vaddsd	xmm0, xmm0, xmm1
	cmp	rdi, rax
	jne	.L3
	vxorps	xmm1, xmm1, xmm1
	vcvtsi2sd	xmm1, xmm1, rdi
	vdivsd	xmm0, xmm0, xmm1
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	vxorps	xmm1, xmm1, xmm1
	vxorpd	xmm0, xmm0, xmm0
	vcvtsi2sd	xmm1, xmm1, rdi
	vdivsd	xmm0, xmm0, xmm1
	ret
	.cfi_endproc
.LFE23:
	.size	very_important_function, .-very_important_function
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
