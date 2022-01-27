.code

EXTERN _ctx_wrap: PROC

ctx_wrap2 PROC
	sub rsp, 16
	and rsp, -16	; TODO: check if -16 is ok
	mov rcx, rsi	; ctx in 0
	mov rdx, rbx	; fun in 1
	mov r8, rdi	; args in 2
	call _ctx_wrap
	ret
ctx_wrap2 ENDP

PUBLIC ctx_link_to
ctx_link_to PROC
	mov r11, [rdx]
	mov [rcx+240], r11	; stack high
	mov [rcx+32], r11	; stack in rsp
	mov r11, [rdx+8]
	mov [rcx+248], r11	; stack low
	mov r11, [rdx+16]
	mov [rcx+256], r11	; stack guard
	mov [rcx], r8		; fun in rbx
	mov [rcx+16], r9	; args in rdi
	mov [rcx+24], rcx	; ctx in rsi
	lea r11, offset ctx_wrap2
	mov [rcx+72], r11	; ctx_wrap2 in rip
	ret
ctx_link_to ENDP

END
