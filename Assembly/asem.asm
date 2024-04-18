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
    lea rsi, [rel text1]
    mov rdx, 19
    call _printText
    call _getName

    lea rsi, [rel text2]
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
    push rbp
    mov rbp, rsp ; Change the base pointer (keeps track of the base of the current stack frame) to the top of the stack pointer

    ; equivalent to push 5
    sub rsp, 4 ; each int is 4 bytes
    mov dword [rbp - 4], 5 ; moves 5 into the stack

    sub rsp, 4
    mov dword [rbp - 8], 0xa
    
    ;sub rsp, 7
    ;lea [rbp - 12], ["tristan"]

    sub rsp, 4
    mov dword [rbp - 12], 9

    mov eax, dword [rbp - 12]
    call _printDigit ; 9

    ;mov rsi, [rbp - 12]
    ;mov rdx, 7
    ;call _printText ; tristan

    mov esi, dword [rbp - 8]
    mov rdx, 1
    call _printText ; newline

    mov eax, dword [rbp - 4]
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
    mov [rel digit], al ;first byte of rax
    
    lea rsi, [rel digit]
    mov rdx, 2
    call _printText
    ret

_endProgram:
    mov rax, 60
    mov rdi, 0
    syscall
    ret

