#include "data.h"
#include "acg.h"

// Functions that add assembly code into outfile

void acg_preamble () {
    fputs(
            "section .data\n" // Data section
            "\tnewline db 0xA\n"
            "_printInteger:\n" // Print Integer Function 
            "\tpush rbp\n"
            "\tmov rbp, rsp\n"
            "\t mov rcx, 10\n"
            "_convertInteger:\n"
            "\txor rdx, rdx\n"
            "\tdiv rcx\n"
            "\tadd rdx, 48\n"
            "\tmov [rsp], dl\n"
            "\tsub rsp, 1\n"
            "\ttest rax, rax\n"
            "\tjnz _convertInteger\n"
            "\tmov rbx, rbp\n"
            "\tsub rbx, rsp\n"
            "\tadd rsp, 1\n"
            "\tmov rax, 1\n"
            "\tmov rdi, 1\n"
            "\tmov rsi, rsp\n"
            "\tmov rdx, rbx\n"
            "\tSyscall\n"
            "\txor rax, rax\n"
            "\tmov rsp, rbp\n"
            "\tpop rbp\n"
            "\tret\n"
            "section .text\n" // Text Section
            "\tglobal _start\n"
            "_start:\n"
            "\tpush rbp\n"
            "\tmov rbp, rsp\n",
    Outfile);
}

void acg_load (int intValue) {
    fprintf(Outfile, "\tpush %d\n", intValue);
}

void acg_printInt (){
    fputs(
            "\tpop rax\n"
            "\tcall _printInteger\n",
    Outfile);
}

void acg_add () {
    fputs(
            "\tpop r8\n"
            "\tpop r9\n"
            "\tadd r9, r8\n"
            "\tpush r9\n"
            "\txor r8, r8\n"
            "\txor r9, r9\n",
    Outfile);
}

void acg_minus () {
    fputs(
            "\tpop r8\n"
            "\tpop r9\n"
            "\tsub r9, r8\n"
            "\tpush r9\n"
            "\txor r8, r8\n"
            "\txor r9, r9\n",
    Outfile);
}

void acg_times () {
    fputs(
            "\tpop r8\n"
            "\tpop rax\n"
            "\tmul r8\n"
            "\tpush rax\n"
            "\txor r8, r8\n"
            "\txor rax, rax\n",
    Outfile);
}

void acg_div () {
    fputs(
            "\tpop r8\n"
            "\tpop rax\n"
            "\txor rdx, rdx\n"
            "\tdiv r8\n"
            "\tpush rax\n"
            "\txor r8, r8\n"
            "\txor rax, rax\n",
    Outfile);
}

void acg_postamble () {
   fputs(
           "\txor rax, rax\n"
           "\tmov rsp, rbp\n"
           "\tpop rbp\n"
           "\tret\n",
    Outfile);
}

