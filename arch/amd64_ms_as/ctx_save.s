	.global ctx_save
	.type ctx_save, @function
ctx_save:
	movq %rbx, (%rcx)
	movq %rbp, 8(%rcx)
	movq %rdi, 16(%rcx)
	movq %rsi, 24(%rcx)
	leaq 8(%rsp), %r11
	movq %r11, 32(%rcx)
	movq %r12, 40(%rcx)
	movq %r13, 48(%rcx)
	movq %r14, 56(%rcx)
	movq %r15, 64(%rcx)
	movq (%rsp), %r11
	movq %r11, 72(%rcx)
	movaps %xmm6, 80(%rcx)
	movaps %xmm7, 96(%rcx)
	movaps %xmm8, 112(%rcx)
	movaps %xmm9, 128(%rcx)
	movaps %xmm10, 144(%rcx)
	movaps %xmm11, 160(%rcx)
	movaps %xmm12, 176(%rcx)
	movaps %xmm13, 192(%rcx)
	movaps %xmm14, 208(%rcx)
	movaps %xmm15, 224(%rcx)
	xorq %rax, %rax
	ret
