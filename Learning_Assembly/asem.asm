section .data
    text1 db "What is your name? "
    text2 db "Hello, "
    digit db 0, 10

section .bss
    name resb 16

section .text
    global _start

_start:
    mov rsi, text1
    mov rdx, 19
    call _printText
    call _getName

    mov rsi, text2
    mov rdx, 7
    call _printText

    mov rsi, name
    mov rdx, 16
    call _printText

    mov rax, 7
    call _printDigit

    mov rdx, 0
    mov rax, 6
    mov rbx, 3
    div rbx

    call _printDigit

    mov rax, 2
    mov rbx, 3
    mul rbx

    call _printDigit


    mov rax, 6
    add rax, 2
    call _printDigit

    call _endProgram

_getName:
    mov rax, 0
    mov rdi, 0
    mov rsi, name
    mov rdx, 16
    syscall
    ret
    
_printText:
    mov rax, 1
    mov rdi, 1
    syscall
    ret

_printDigit:
    add rax, 48
    mov [digit], al ;first byte of rax
    
    mov rsi, digit
    mov rdx, 2
    call _printText
    ret

_endProgram:
    mov rax, 60
    mov rdi, 0
    syscall
    ret

