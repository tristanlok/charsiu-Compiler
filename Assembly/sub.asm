section .text
    global _start

_start:
   
    ; Setup

    push 4233 ; Pushes the first number onto the stack

    push 1231 ; Pushes the second number onto the stack

    ; Code

    pop r8
    pop r9

    sub r9, r8

    push r9

    mov rax, 60
    mov rdi, 0
    Syscall
