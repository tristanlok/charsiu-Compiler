section .data
    text1 db "What is your name? "
    text2 db "Hello, "
    digit db 0, 10

section .bss
    name resb 16

section .text
    global _start

_start:
    
    ; Inputing and Outputting Text
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

    ; Outputting Numbers and performing Arithmetic
    mov rax, 7
    call _printDigit ; 7

    mov rdx, 0
    mov rax, 6
    mov rbx, 3
    div rbx

    call _printDigit ; 2

    mov rax, 2
    mov rbx, 3
    mul rbx

    call _printDigit ; 6

    mov rax, 6
    add rax, 2
    call _printDigit ; 8

    ; Stack Operations and storing values in the stack

    ; Stack pointers can Increment/Decrement + Pre-/Post-
    ; x86-64 decrements when we call push
    mov rbp, rsp ; Change the base pointer (keeps track of the base of the current stack frame) to the top of the stack pointer

    push 5

    push 0xa ; ascii for newline

    mov rax, "tristan"
    push rax

    push 1

    pop rax
    call _printDigit ; 1

    mov rsi, rsp ; same as lea rsi, [rsp]
    mov rdx, 7
    call _printText ; tristan

    add rsp, 8

    mov rsi, rsp
    mov rdx, 1

    call _printText ; newline

    add rsp, 8 ; Always increment by 8 as push function always pushes 64 bit

    pop rax
    call _printDigit ; 5

    ; Ends the program
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

