section .text
    global _start

; prints 32 bit integer
; Converts Integers to ASCII

_start: 
    ; Setup

    push rbp
    mov rbp, rsp

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

    ; Expects integer value in (eax/rax)
    call _printInteger

    mov rax, 60
    mov rdi, 0
    Syscall


_printInteger:
    ; Creating a new Function Frame
    push rbp
    mov rbp, rsp

    mov rcx, 10

_convertInteger:
    xor rdx, rdx ; clear rdx

    ; divide number by 10, rax <- resultant, rdx <- remainder
    div rcx

    add rdx, 48 ; Convert Int to Ascii

    mov [rsp], dl ; Moving Byte 0 of rdx into the stack
    sub rsp, 1

    test rax, rax ; checks to see if rax is empty, will affect the z flag

    jnz _convertInteger ; jumps back to the top if z flag doesn't show 1

    
    mov rbx, rbp ; this will be the register holding the size of the integer
    sub rbx, rsp ; rbp - rsp

    ; Account for the extra decrease in rsp
    add rsp, 1

    ; Prints the result

    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, rbx
    Syscall

    mov rsp, rbp ; important step of the postamble
    pop rbp ; returns the previous base pointer back

    ret

