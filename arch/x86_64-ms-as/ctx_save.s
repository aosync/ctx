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
	movq %gs:0x30, %r8	# TIB pointer
	movq 0x8(%r8), %r9
	movq %r9, 240(%rcx)	# save stack high
	movq 0x10(%r8), %r9
	movq %r9, 248(%rcx)	# save stack low
	movq 0x1478(%r8), %r9
	movq %r9, 256(%rcx)	# save stack guard
	xorq %rax, %rax
	ret
