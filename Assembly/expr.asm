; Performing (2 + 3) x 5 - 8 / 3

section .text
    global _start

_start:
    ; Initialize stack
    push rbp
    mov rbp, rsp

    ; Loading first 2 integer

    sub rsp, 4
    mov dword [rbp - 4], 2
    
    sub rsp, 4
    mov dword [rbp - 8], 3

    ; Perform addition (2 + 3)

    mov eax, dword [rbp - 4]
    mov edx, dword [rbp - 8]

    add eax, edx

    sub rsp, 4
    mov dword [rbp - 12], eax

    ; Load next integer

    sub rsp, 4
    mov dword [rbp - 16], 5

    ; Perform Multiplication (5 * 5)

    mov eax, dword [rbp - 12]

    mul dword [rbp - 16]
 
    sub rsp, 4
    mov dword [rbp - 20], eax

    ; Load next integer

    sub rsp, 4
    mov dword [rbp - 24], 8

    sub rsp, 4
    mov dword [rbp - 28], 3

    ; Perform Division (8 / 3)

    mov eax, dword [rbp - 24]

    xor rdx, rdx
    div dword [rbp - 28]

    sub rsp, 4
    mov dword [rbp - 32], eax

    ; Perform Subtraction

    mov eax, dword [rbp - 20]
    mov edx, dword [rbp - 32]

    sub eax, edx

    sub rsp, 4
    mov dword [rbp - 36], eax

    mov rax, 60
    mov rdi, 0
    syscall
