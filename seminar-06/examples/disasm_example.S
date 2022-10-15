	.file	"disasm_example.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	calculate
	.type	calculate, @function
calculate:
.LFB23:
	.cfi_startproc
	endbr64
	lea	eax, [rdi+rsi]
	imul	eax, esi
	cdqe
	add	rax, rdx
	ret
	.cfi_endproc
.LFE23:
	.size	calculate, .-calculate
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d"
.LC1:
	.string	"%ld\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	endbr64
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	lea	rdi, .LC0[rip]
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 8[rsp], rax
	xor	eax, eax
	lea	rsi, 4[rsp]
	mov	DWORD PTR 4[rsp], 0
	call	__isoc99_scanf@PLT
	mov	eax, DWORD PTR 4[rsp]
	mov	edi, 1
	lea	rsi, .LC1[rip]
	lea	edx, 1[rax]
	xor	eax, eax
	movsx	rdx, edx
	call	__printf_chk@PLT
	mov	rax, QWORD PTR 8[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L6
	xor	eax, eax
	add	rsp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L6:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE24:
	.size	main, .-main
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
