	.intel_syntax noprefix
	.text
	.global ctx_jmp
	.type ctx_save, @function
ctx_jmp:
	MOV RBX, qword ptr[RDI]
	MOV RSP, qword ptr[RDI+8]
	MOV RBP, qword ptr[RDI+16]
	MOV R12, qword ptr[RDI+24]
	MOV R13, qword ptr[RDI+32]
	MOV R14, qword ptr[RDI+40]
	MOV R15, qword ptr[RDI+48]
	MOV RAX, RSI
	JMP [RDI+56]
