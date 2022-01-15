global ft_memcpy:function ; void *memcpy(void *dest, const void *src, size_t n);
section .text

ft_memcpy:
			push rdi
			xor rcx, rcx
	.loop:
			cmp rcx, rdx
			je .return
			mov al, byte [rsi + rcx]
			mov byte [rdi + rcx], al
			inc rcx
			jmp .loop
	.return:
			pop rax
			ret