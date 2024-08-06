    .global ctx_jmp
ctx_jmp:
    movq (%rcx), %rbx
    movq 8(%rcx), %rbp
    movq 16(%rcx), %rdi
    movq 24(%rcx), %rsi
    movq 32(%rcx), %rsp
    movq 40(%rcx), %r12
    movq 48(%rcx), %r13
    movq 56(%rcx), %r14
    movq 64(%rcx), %r15
    movaps 80(%rcx), %xmm6
    movaps 96(%rcx), %xmm7
    movaps 112(%rcx), %xmm8
    movaps 128(%rcx), %xmm9
    movaps 144(%rcx), %xmm10
    movaps 160(%rcx), %xmm11
    movaps 176(%rcx), %xmm12
    movaps 192(%rcx), %xmm13
    movaps 208(%rcx), %xmm14
    movaps 224(%rcx), %xmm15
    movq %gs:0x30, %r8		# TIB pointer
    movq 240(%rcx), %r9
    movq %r9, 0x8(%r8)		# stack high
    movq 248(%rcx), %r9
    movq %r9, 0x10(%r8)		# stack low
    movq 256(%rcx), %r9
    movq %r9, 0x1478(%r8)	# stack guard
    movq %rdx, %rax
    jmp *72(%rcx)
