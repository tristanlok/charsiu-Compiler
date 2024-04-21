; DATA SECTION for all strings + escape sequences

; Assembly x86-64 code for charsiu after optimization: print("test 1\t%i \n%s", (1 + 2), "te\tst");

; in node thats [PRINT | "test 1\t%i \n%s"] -> (L) [3] -> (R) ["test"]

; keep track of free registers and use those here asides from rax and stuff

; Check and ensure that I am using Proper registry conventional use

section .data
    newline db 0xA
    tab db "        "
    whack db 92
    tick db 39
    quote db 34
    percentage db 37

    ; User strings goes here
    str_1 .asciz "te\tst"
    str_2 .asciz "test 1\t%i \n%s"

section .bss

section .text
    global _start

; Deals with escape sequences

_escapeSeq:
    add rbx, 1 ; increments to the next character

    cmp [r8 + rbx], 110 ; \n
    je _newline

    cmp [r8 + rbx], 116 ; \t
    je _tab

    cmp [r8 + rbx], 92 ; \\
    je _whack

    cmp [r8 + rbx], 39 ; \'
    je _tick

    cmp [r8 + rbx], 34 ; \"
    je _quote

    ret

; Prints the specified escape sequence

_newline:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel newline]
    mov rdx, 1
    syscall
    ret

_tab:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel tab]
    mov rdx, 8
    syscall
    ret

_whack:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel whack]
    mov rdx, 1
    syscall
    ret

_tick:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel tick]
    mov rdx, 1
    syscall
    ret

_quote:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel quote]
    mov rdx, 1
    syscall
    ret

; Deals with Format Specifier

_formatSpec:
    add rbx, 1 ; increment to the next character

    cmp [r8 + rbx], 105 ; %i
    je _intArg

    cmp [r8 + rbx], 115 ; %s
    je _stringArg

    cmp [r8 + rbx], 37 ; %%
    je _percentageArg

    ret

; Prints the specific value

_stringArg:
    add r9, 8 ; Increment r9 by as the size of string pointer is 8 bytes, (to be decremented as we are looking down)

    lea rsi, [rbp - r9] ; Gets the current argument

    call _printStr

    ret

_percentageArg:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel percentage]
    mov rdx, 1
    syscall
    ret

; Main Print Function

_printChar:     ; Requires RSI and RDX to be set before hand
    mov rax, 1
    mov rdi, 1
    syscall
    ret

; Prints String Arguments

_printStr:
    ; Given that the string pointer is in rsi
    xor r10, r10 ; clears a temp reg for counting

_printStrloop:
    ; ESCAPE SEQ SUBROUTINE NEEDS TO BE UPDATED TO SUPPORT VARIOUS CALLS
    cmp [r8 + r10], 92 ; check if character is whack (escape sequence)
    je _escapeSeq

    ; Prints current character if != escape sequence
    lea rsi, [r8 + r10]
    mov rdi, 1
    jne _printChar

    ; Increments to the next character
    add r10, 1

    cmp [rax + r10], 0 ; Check if the next character is a null terminator
    jne _printStrLoop ; if does not equal null terminator, loop back

    ret


; Prints Int Arguments

_printInt:
    ; Creating a new Function Frame
    push rbp
    mov rbp, rsp

    mov rcx, 10

_convertInt:
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

; Print formatted String

_checkFormat:
    cmp [r8 + rbx], 37 ; check if character is percentage (format specifier) 
    je _formatSpec

    ; Prints current character if != formatted string
    lea rsi, [r8 + rbx]
    mov rdi, 1
    jne _printChar


    ret

_printf:
    mov r8, rax ; moves the pointer from rax to rdx
    xor r9, r9 ; clearing r9 to use to determine location of format specifier % value
    xor rbx, rbx ; clearing rbx to be used as counter/index

_printfloop:
    ; Checks for special cases
    cmp [r8 + rbx], 92 ; check if character is whack (escape sequence)
    je _escapeSeq

    ; (else if statement) prints character if not format string
    jne _checkFormat

    add rbx, 1    

    cmp [r8 + rbx], 0 ; check if next character is a null terminator
    jne _printfloop

    ret

_start:
    push rbp
    mov rbp, rsp

    sub rsp, 4
    mov dword [rbp - 4], 3

    ; Pointers are 8 bytes
    sub rsp, 8
    lea rax, [rel str_1]
    mov qword [rbp - 8], rax

    lea rax, [rel str_2]

    call _printf
