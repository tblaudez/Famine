global ft_memmem:function
section .text

ft_memmem:
			dec rsi
			dec rcx
			mov r8, -1
	.loop1:
			inc r8
			cmp r8, rsi
			jg .return_null
			mov r9, -1
		.loop2:
			inc r9
			mov rax, r8
			add rax, r9
			cmp rax, rsi
			jg .loop1

			mov al, byte [rdi + rax]
			cmp al, byte [rdx + r9]
			jne .loop1

			cmp r9, rcx
			je .return_ptr

			jmp .loop2

	.return_null:
			mov rax, 0
			ret
	.return_ptr:
			lea rax, [rdi + r8]
			ret
