	.intel_syntax noprefix
	.text
	.global ctx_save
	.type ctx_save, @function
ctx_save:
	MOV qword ptr[RDI], RBX
	LEA RCX, [RSP+8]
	MOV qword ptr[RDI+8], RCX
	MOV qword ptr[RDI+16], RBP
	MOV qword ptr[RDI+24], R12
	MOV qword ptr[RDI+32], R13
	MOV qword ptr[RDI+40], R14
	MOV qword ptr[RDI+48], R15
	MOV RCX, qword ptr[RSP]
	MOV qword ptr[RDI+56], RCX
	XOR RAX, RAX
	RET
