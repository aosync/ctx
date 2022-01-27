	.global ctx_link_to
	.type ctx_link_to, @function
ctx_link_to:
	movq %rdx, 32(%rcx)	# stack in rsp
	movq %r8, (%rcx)	# fun in rbx
	movq %r9, 16(%rcx)	# args in rdi
	movq %rcx, 24(%rcx)	# ctx in rsi
	leaq ctx_wrap2(%rip), %r11
	movq %r11, 72(%rcx)	# ctx_wrap2 in rip
	ret
ctx_wrap2:
	subq $16, %rsp
	andq $~15, %rsp
	movq %rsi, %rcx		# ctx in 0
	movq %rbx, %rdx		# fun in 1
	movq %rdi, %r8 		# args in 2
	call _ctx_wrap
	ret
	