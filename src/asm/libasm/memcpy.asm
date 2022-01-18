global ft_memcpy:function ; void *memcpy(void *dest, const void *src, size_t n);
section .text

ft_memcpy:
			mov rax, rdi
			mov rcx, rdx
			repnz movsb
			ret