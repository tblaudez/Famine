global ft_strlen:function ; size_t ft_strlen(const char *s)
section	.text

ft_strlen:
			xor		rax, rax
	.loop:
			cmp		byte [rdi + rax], 0
			jz		.return
			inc		rax
			jmp		.loop
	.return:
			ret