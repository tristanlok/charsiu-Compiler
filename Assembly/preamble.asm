section .data
    newline db 0xA ; Create a newline

; SUBROUTINES GOES HERE

; Print Integer SubRoutine
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

section .text
    global _start

_start:
    push rbp
    mov rbp, rsp
