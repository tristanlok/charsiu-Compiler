section .text
    global _start

_start:
   
    ; Setup

    push 90 ; Pushes the first number onto the stack

    push 30 ; Pushes the second number onto the stack

    ; Code

    pop r8
    pop rax

    mov rdx, 0

    div r8

    ; rdx will hold the remainder after division

    push rax

    mov rax, 60
    mov rdi, 0
    Syscall
