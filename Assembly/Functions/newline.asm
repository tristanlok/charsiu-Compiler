section .data
    newline db 0xA

section .text
    global _start

; prints 32 bit integer
; Converts Integers to ASCII

_start: 
    ; Print newline
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    Syscall

    mov rax, 60
    mov rdi, 0
    Syscall

