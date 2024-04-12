section .text
    global _start

_start:
   
    ; Setup

    push 23 ; Pushes the first number onto the stack

    push 90 ; Pushes the second number onto the stack

    ; Code

    pop r8
    pop rax

    mul r8

    push rax

    mov rax, 60
    mov rdi, 0
    Syscall
