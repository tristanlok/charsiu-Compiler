; DATA SECTION for all strings + escape sequences

; Assembly x86-64 code for charsiu after optimization: print("test 1\t%i \n%s", (1 + 2), "test");

; in node thats [PRINT | "test 1\t%i \n%s"] -> (L) [3] -> (R) ["test"]

; keep track of free registers and use those here asides from rax and stuff

section .data
   newline db 0xA
   tab db "        "
   whack db 92
   tick db 39
   quote db 34
   percentage db 37
   str_1 .asciz "test"
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

    add rbx, 1 ; increments to the next character completing the escape sequence
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
    je _newline

    cmp [r8 + rbx], 115 ; %s
    je _tab

    cmp [r8 + rbx], 37 ; %%
    je _percentage

    add rbx, 1 ; increments to the next character completing the escape sequence
    ret

; Prints the specific value


_percentage:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel percentage]
    mov rdx, 1
    syscall
    ret

; Main Print Function

_print:
    

_printloop:

_printf:
    mov r8, rax ; moves the pointer from rax to rdx
    xor r9, r9 ; clearing r9 to use to determine location of format specifier % value
    xor rbx, rbx ; clearing rbx to be used as counter/index

_printfloop:
    cmp [r8 + rbx], 0 ; check if character is a null terminator
    je _exit ; to be defined later

    cmp [r8 + rbx], 92 ; check if character is whack (escape sequence)
    je _escapeSeq

    cmp [r8 + rbx], 37 ; check if character is percentage (format specifier) 

    

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

    call _print
