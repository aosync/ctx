	.global ctx_link_to
	.type ctx_link_to, @function
ctx_link_to:
	movq %rsi, 8(%rdi)	# stack in rsp
	movq %rdx, (%rdi)	# fun in rbx
	movq %rcx, 24(%rdi)	# args in r12
	movq %rdi, 32(%rdi)	# ctx in r13
	leaq ctx_wrap2(%rip), %r11
	movq %r11, 56(%rdi)	# ctx_wrap2 in rip
	ret
ctx_wrap2:
	subq $16, %rsp
	andq $~15, %rsp
	movq %r13, %rdi		# ctx in 0
	movq %rbx, %rsi		# fun in 1
	movq %r12, %rdx		# args in 2
	call _ctx_wrap
	ret
