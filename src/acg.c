#include "data.h"
#include "defs.h"
#include "acg.h"

static void verifyCharAlloc (int currLen, int maxLen, char *src, char *dest) {
    if ((currLen + strlen(src)) > maxLen) {
        dest = realloc(dest, sizeof(char) * (currLen + maxLen));
    }
}

// Functions that add assembly code into outfile

void acg_preamble () {
    char dataSec[] = (
            "section .data\n"
            "\tnewline db 0xA\n");

    char textSec[] = (
            "section .text\n" // Text Section
            "\tglobal _start\n"
            "_printInteger:\n" // Print Integer Function 
            "\tpush rbp\n"
            "\tmov rbp, rsp\n"
            "\tmov rcx, 10\n"
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
            "_start:\n"
            "\tpush rbp\n"
            "\tmov rbp, rsp\n");

    verifyCharAlloc(dataLen, DATA_MAX_LEN, dataSec, asmData);
    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    strcat(asmData, dataSec);
    strcat(asmText, textSec);
}

void acg_loadInt (int intValue) {
    char text[] = 
        ("\tpush %d\n");

    int max = 50;
    char textSec[max];

    int size = snprintf(textSec, max, text, intValue);

    // this is done to prevent seg fault
    if (size > max) {
        char newTextSec[size];
        sprintf(newTextSec, text, intValue);
        verifyCharAlloc(textLen, TEXT_MAX_LEN, newTextSec, asmText);
        strcat(asmText, newTextSec);

    } else {
        verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);
        strcat(asmText, textSec);
    }
}

void acg_loadStr (char *strValue) {
    
}

void acg_printInt () {
    char textSec[] =
        ("\tpop rax\n"
         "\tcall _printInteger\n");

    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    strcat(asmText, textSec);
}

void acg_add () {
    char textSec[] =
        ("\tpop r8\n"
        "\tpop r9\n"
        "\tadd r9, r8\n"
        "\tpush r9\n"
        "\txor r8, r8\n"
        "\txor r9, r9\n");

    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    strcat(asmText, textSec);
}

void acg_minus () {
    char textSec[] =
        ("\tpop r8\n"
        "\tpop r9\n"
        "\tsub r9, r8\n"
        "\tpush r9\n"
        "\txor r8, r8\n"
        "\txor r9, r9\n");

    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    strcat(asmText, textSec);
}

void acg_times () {
    char textSec[] =
        ("\tpop r8\n"
        "\tpop rax\n"
        "\tmul r8\n"
        "\tpush rax\n"
        "\txor r8, r8\n"
        "\txor rax, rax\n");

    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    strcat(asmText, textSec);
}

void acg_div () {
    char textSec[] =
        ("\tpop r8\n"
        "\tpop rax\n"
        "\tdiv r8\n"
        "\tpush rax\n"
        "\txor r8, r8\n"
        "\txor rax, rax\n");

    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    strcat(asmText, textSec);
}

void acg_postamble () {
    char textSec[] =
        ("\txor rax, rax\n"
        "\tmov rsp, rbp\n"
        "\tpop rbp\n"
        "\tmov rax, 60\n"
        "\tmov rdi, 0\n"
        "\tsyscall\n");

    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    strcat(asmText, textSec);
}

