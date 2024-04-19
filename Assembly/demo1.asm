; DATA SECTION for all strings + escape sequences

; Assembly x86-64 code for charsiu after optimization: print("test 1\t%i \n%s", (1 + 2), "test");

; in node thats [PRINT] -> ["test 1\t%i \n%s"] -> (L) [3] -> (R) ["test"]

section .data
   newline db 0xA
   tab db "        "
   str_1 .asciz "test"

section .bss

section .text
    global _start

_start:
     push rbp
     mov rbp, rsp

     sub rsp, 4
     mov dword [rbp - 4], 3

     sub rsp, 4
     lea [rbp - 4], str_1
