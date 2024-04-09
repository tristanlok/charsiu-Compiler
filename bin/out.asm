section .data
	newline db 0xA
section .text
	global _start
_printInteger:
	push rbp
	mov rbp, rsp
	mov rcx, 10
_convertInteger:
	xor rdx, rdx
	div rcx
	add rdx, 48
	mov [rsp], dl
	sub rsp, 1
	test rax, rax
	jnz _convertInteger
	mov rbx, rbp
	sub rbx, rsp
	add rsp, 1
	mov rax, 1
	mov rdi, 1
	mov rsi, rsp
	mov rdx, rbx
	Syscall
	xor rax, rax
	mov rsp, rbp
	pop rbp
	ret
_start:
	push rbp
	mov rbp, rsp
	push 2
	push 3
	push 5
	pop r8
	pop rax
	mul r8
	push rax
	xor r8, r8
	xor rax, rax
	pop r8
	pop r9
	add r9, r8
	push r9
	xor r8, r8
	xor r9, r9
	push 8
	push 3
	pop r8
	pop rax
	xor rdx, rdx
	div r8
	push rax
	xor r8, r8
	xor rax, rax
	pop r8
	pop r9
	sub r9, r8
	push r9
	xor r8, r8
	xor r9, r9
	pop rax
	call _printInteger
	xor rax, rax
	mov rsp, rbp
	pop rbp
	mov rax, 60
	mov rdi, 0
	syscall

