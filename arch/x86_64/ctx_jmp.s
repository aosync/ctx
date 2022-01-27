	.global ctx_jmp
	.type ctx_save, @function
ctx_jmp:
	movq (%rdi), %rbx
	movq 8(%rdi), %rsp
	movq 16(%rdi), %rbp
	movq 24(%rdi), %r12
	movq 32(%rdi), %r13
	movq 40(%rdi), %r14
	movq 48(%rdi), %r15
	movq %rsi, %rax
	jmp 56(%rdi)
