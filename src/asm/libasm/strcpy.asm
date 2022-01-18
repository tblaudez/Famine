global ft_strcpy:function ; char *ft_strcpy(char *dst, const char *src)
extern ft_strlen
section	.text

ft_strcpy:
			push rdi
	.getSize:
			xchg rdi, rsi
			call ft_strlen
			mov rcx, rax
			xchg rdi, rsi
	.copyString:
			repnz movsb
			mov byte [rdi], 0
	.return:
			pop rax
			ret