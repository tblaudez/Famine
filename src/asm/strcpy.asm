global ft_strcpy:function ; char *ft_strcpy(char *dst, const char *src)
section	.text

ft_strcpy:
			push	rdi
			xor		rcx, rcx
	.loop:
			cmp		byte [rsi + rcx], 0
			jz		.done
			mov		al, byte [rsi + rcx]
			mov		byte [rdi+rcx], al
			inc		rcx
			jmp		.loop
	.done:
			mov		[rdi+rcx], byte 0
			pop		rax
			ret