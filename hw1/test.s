	.file	"test.c"
	.local	state
	.comm	state,4,4
	.section	.rodata
.LC0:
	.string	"RED"
.LC1:
	.string	"GREEN"
.LC2:
	.string	"YELLOW"
	.text
	.globl	stop_light
	.type	stop_light, @function
stop_light:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	state(%rip), %eax
	cmpl	$1, %eax
	je	.L3
	cmpl	$2, %eax
	je	.L4
	testl	%eax, %eax
	jne	.L10
	movl	$.LC0, %edi
	call	puts
	movl	state_counter.2185(%rip), %eax
	addl	$1, %eax
	movl	%eax, state_counter.2185(%rip)
	movl	state_counter.2185(%rip), %eax
	cmpl	$4, %eax
	jle	.L6
	movl	$0, state_counter.2185(%rip)
	movl	$2, state(%rip)
	jmp	.L1
.L6:
	jmp	.L1
.L4:
	movl	$.LC1, %edi
	call	puts
	movl	state_counter.2185(%rip), %eax
	addl	$1, %eax
	movl	%eax, state_counter.2185(%rip)
	movl	state_counter.2185(%rip), %eax
	cmpl	$4, %eax
	jle	.L8
	movl	$0, state_counter.2185(%rip)
	movl	$1, state(%rip)
	jmp	.L1
.L8:
	jmp	.L1
.L3:
	movl	$.LC2, %edi
	call	puts
	movl	state_counter.2185(%rip), %eax
	addl	$1, %eax
	movl	%eax, state_counter.2185(%rip)
	movl	state_counter.2185(%rip), %eax
	cmpl	$1, %eax
	jle	.L9
	movl	$0, state_counter.2185(%rip)
	movl	$0, state(%rip)
	jmp	.L1
.L9:
	jmp	.L1
.L10:
	movl	$0, state(%rip)
	movl	$0, state_counter.2185(%rip)
	nop
.L1:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	stop_light, .-stop_light
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	jmp	.L12
.L13:
	movl	$0, %eax
	call	stop_light
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	inc
	movl	%eax, -4(%rbp)
.L12:
	cmpl	$35, -4(%rbp)
	jle	.L13
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.local	state_counter.2185
	.comm	state_counter.2185,4,4
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-4)"
	.section	.note.GNU-stack,"",@progbits
