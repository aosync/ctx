.code

ctx_save PROC
    mov [rcx], rbx
    mov [rcx+8], rbp
    mov [rcx+16], rdi
    mov [rcx+24], rsi
    lea r11, [rsp+8]
    mov [rcx+32], r11
    mov [rcx+40], r12
    mov [rcx+48], r13
    mov [rcx+56], r14
    mov [rcx+64], r15
    mov r11, [rsp]
    mov [rcx+72], r11
    movaps [rcx+80], xmm6
    movaps [rcx+96], xmm7
    movaps [rcx+112], xmm8
    movaps [rcx+128], xmm9
    movaps [rcx+144], xmm10
    movaps [rcx+160], xmm11
    movaps [rcx+176], xmm12
    movaps [rcx+192], xmm13
    movaps [rcx+208], xmm14
    movaps [rcx+224], xmm15
    mov r8, gs:[30h]	; TIB pointer
    mov r9, [r8+8h]
    mov [rcx+240], r9	; stack high
    mov r9, [r8+10h]
    mov [rcx+248], r9	; stack low
    mov r9, [r8+1478h]
    mov [rcx+256], r9	; stack guard
    xor rax, rax
    ret
ctx_save ENDP

END
