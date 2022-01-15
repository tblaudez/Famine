global syscall_wrapper:function
section .text

syscall_wrapper:
			mov rax, rdi
			mov rdi, rsi
			mov rsi, rdx
			mov rdx, rcx
			mov r10, r8
			mov r8, r9
			mov r9, qword [rsp + 8]
			syscall
			mov rdi, -4095
			cmp rdi, rax
			jae .return
	.error:
			mov rax, -1
	.return:
			ret