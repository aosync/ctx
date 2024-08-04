.code

ctx_jmp PROC
    mov rbx, [rcx]
    mov rbp, [rcx+8]
    mov rdi, [rcx+16]
    mov rsi, [rcx+24]
    mov rsp, [rcx+32]
    mov r12, [rcx+40]
    mov r13, [rcx+48]
    mov r14, [rcx+56]
    mov r15, [rcx+64]
    movaps xmm6, [rcx+80]
    movaps xmm7, [rcx+96]
    movaps xmm8, [rcx+112]
    movaps xmm9, [rcx+128]
    movaps xmm10, [rcx+144]
    movaps xmm11, [rcx+160]
    movaps xmm12, [rcx+176]
    movaps xmm13, [rcx+192]
    movaps xmm14, [rcx+208]
    movaps xmm15, [rcx+224]
    mov r8, gs:[30h]	; TIB pointer
    mov r9, [rcx+240]
    mov [r8+8h], r9	; stack high
    mov r9, [rcx+248]
    mov [r8+10h], r9	; stack low
    mov r9, [rcx+256]
    mov [r8+1478h], r9	; stack guard
    mov rax, rdx
    jmp qword ptr [rcx+72]
ctx_jmp ENDP

END
