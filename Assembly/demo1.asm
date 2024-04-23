; DATA SECTION for all strings + escape sequences

; Assembly x86-64 code for charsiu after optimization: print("test 1\t%i \n%s", (1 + 2), "te\tst");

; in node thats [PRINT | "test 1\t%i \n%s"] -> (L) [3] -> (R) ["test"]

; keep track of free registers and use those here asides from rax and stuff

; Check and ensure that I am using Proper registry conventional use

section .data
    newline db 0xA
    percentage db 37

    ; User strings goes here
    str_1 db `te\tst`, 0
    str_2 db `test 1\t%i \n%s`, 0

section .bss

section .text
    global _start

; Deals with Format Specifier

_formatSpec:
    add rbx, 1 ; increment to the next character

    cmp byte [r8 + rbx], 105 ; %i
    je _intArg

    cmp byte [r8 + rbx], 115 ; %s
    je _stringArg

    cmp byte [r8 + rbx], 37 ; %%
    je _percentageArg

    ret

; Prints the specific value

_intArg:
    add rcx, 4 ;Increment r9 by the size of an integer which is 4 bytes (decremented)

    mov rax, rbp ; we perform this as we cannot perform address - address
    sub rax, rcx

    lea eax, [rax] ; we only want 4 bytes therefore it is eax

    call _printInt

    ret

_stringArg:
    add rcx, 8 ; Increment r9 by the size of string pointer is 8 bytes, (to be decremented as we are looking down)

    mov rax, rbp
    sub rax, rcx

    lea rsi, [rax] ; Gets the current argument

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

_printStrLoop:
    ; Prints current character if != escape sequence
    lea rsi, [r8 + r10]
    mov rdi, 1
    call _printChar

    ; Increments to the next character
    add r10, 1

    cmp byte [rax + r10], 0 ; Check if the next character is a null terminator
    jne _printStrLoop ; if does not equal null terminator, loop back

    ret


; Prints Int Arguments

_printInt:
    ; Given that the integer is in eax
    push rbp
    mov rbp, rsp

    mov ecx, 10

_convertInt:
    xor rdx, rdx ; clear rdx

    ; divide number by 10, rax <- resultant, rdx <- remainder
    div ecx

    add edx, 48 ; Convert Int to Ascii

    mov [rsp], dl ; Moving Byte 0 of rdx into the stack
    sub rsp, 1

    test eax, eax ; checks to see if rax is empty, will affect the z flag

    jnz _convertInt ; jumps back to the top if z flag doesn't show 1

    
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

    ret

; Print formatted String

_printf:
    mov r8, rax ; moves the pointer from rax to rdx
    xor rcx, rcx ; clearing r9 to use to determine location of format specifier % value
    xor rbx, rbx ; clearing rbx to be used as counter/index

_printfloop:
    ; Checks for special cases
    cmp byte [r8 + rbx], 37 ; check if character is percentage (format specifier)
    je _formatSpec

    ; Prints current character if != formatted string
    lea rsi, [r8 + rbx]
    mov rdi, 1
    jne _printChar

    add rbx, 1    

    cmp byte [r8 + rbx], 0 ; check if next character is a null terminator
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

    mov rax, 60
    mov rdi, 0
    syscall
