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
    mov rax, rdx
    jmp [rcx+72]
ctx_jmp ENDP

END
