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
    ; Assumes string is stored in rax
    add rbx, 1 ; increment to the next character

    cmp byte [rax + rbx], 115 ; %s
    je _stringArg

    cmp byte [rax + rbx], 105 ; %i
    je _intArg

    cmp byte [rax + rbx], 37 ; %%
    je _percentageArg

    ; ret - no need for return as the above jumps should return back to printfloop

; Prints the specific value

_stringArg:
    add r13, 8 ; Increment r9 by the size of string pointer is 8 bytes, (to be decremented as we are looking down)

    mov rax, rbp
    sub rax, r13

    mov rax, [rax]

    call _printStr

    ret

_intArg:
    add r13, 4 ;Increment r9 by the size of an integer which is 4 bytes (decremented)

    mov rax, rbp ; we perform this as we cannot perform address - address
    sub rax, r13

    mov eax, [rax] ; we only want 4 bytes therefore it is eax (mov since we want the value)

    call _printInt

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
    ; Given that the string pointer is in rax
    xor r12, r12 ; clears the rcx reg for counting

_printStrLoop:
    push rax ; saves rax
    ; Prints current character if != escape sequence
    lea rsi, [rax + r12]
    mov rdx, 1
    call _printChar

    pop rax

    ; Increments to the next character
    add r12, 1

    cmp byte [rax + r12], 0 ; Check if the next character is a null terminator
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

    sub rsp, 1
    mov [rsp], dl ; Moving Byte 0 of rdx into the stack

    test eax, eax ; checks to see if rax is empty, will affect the z flag

    jnz _convertInt ; jumps back to the top if z flag doesn't show 1

    
    mov r8, rbp ; this will be the register holding the size of the integer
    sub r8, rsp ; rbp - rsp

    ; Account for the extra decrease in rsp
    ; add rsp, 1

    ; Prints the result

    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, r8
    Syscall

    add rsp, r8 ; move back to rbp

    pop rbp ; fix rbp

    ret

; Print formatted String

_printf:
    xor r13, r13 ; determine location of format specifier % value
    xor rbx, rbx ; clearing rbx to be used as counter/index

_printfloop:
    push rax ; saves the pointer at rax

    push _printfloopEnd ; pushes address of end for jump to return back to

    ; Checks for special cases
    cmp byte [rax + rbx], 37 ; check if character is percentage (format specifier)
    je _formatSpec

    ; Prints current character if != formatted string
    lea rsi, [rax + rbx]
    mov rdx, 1
    
    jne _printChar

_printfloopEnd:

    pop rax ; fixes the pointer in rax

    add rbx, 1

    cmp byte [rax + rbx], 0 ; check if next character is a null terminator
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
    mov qword [rbp - 12], rax

    lea rax, [rel str_2]

    call _printf

    mov rax, 60
    mov rdi, 0
    syscall
