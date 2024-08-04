	.global ctx_save
	.type ctx_save, @function
ctx_save:
	movq %rbx, (%rdi)
	leaq 8(%rsp), %rcx
	movq %rcx, 8(%rdi)
	movq %rbp, 16(%rdi)
	movq %r12, 24(%rdi)
	movq %r13, 32(%rdi)
	movq %r14, 40(%rdi)
	movq %r15, 48(%rdi)
	movq (%rsp), %rcx
	movq %rcx, 56(%rdi)
	xorq %rax, %rax
	ret
