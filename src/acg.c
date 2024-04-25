#include "data.h"
#include "defs.h"
#include "acg.h"

static void verifyCharAlloc (int currLen, int maxLen, char *src, char *dest) {
    if ((currLen + strlen(src)) > maxLen) {
        dest = realloc(dest, sizeof(char) * (currLen + strlen(src) + maxLen));
    }
}

// Functions that add assembly code into outfile

void acg_preamble () {
    char dataSec[] = (
            "section .data\n"
            "\tnewline db 0xA\n"
            "\tpercentage db 37\n");    

    char textSec[] = (
            "section .text\n"
            "\tglobal _start\n"
            "_formatSpec:\n"
            "\tadd rbx, 1\n"
            "\tcmp byte [rax + rbx], 115\n"
            "\tje _stringArg\n"
            "\tcmp byte [rax + rbx], 105\n"
            "\tje _intArg\n"
            "\tcmp byte [rax + rbx], 37\n"
            "\tje _percentageArg\n"
            "_stringArg:\n"
            "\tadd r13, 8\n"
            "\tmov rax, rbp\n"
            "\tsub rax, r13\n"
            "\tmov rax, [rax]\n"
            "\tcall _printStr\n"
            "\tret\n"
            "_intArg:\n"
            "\tadd r13, 8\n"
            "\tmov rax, rbp\n"
            "\tsub rax, r13\n"
            "\tmov eax, [rax]\n"
            "\tcall _printInt\n"
            "\tret\n"
            "_percentageArg:\n"
            "\tmov rax, 1\n"
            "\tmov rdi, 1\n"
            "\tlea rsi, [rel percentage]\n"
            "\tmov rdx, 1\n"
            "\tsyscall\n"
            "\tret\n"
            "_printChar:\n"
            "\tmov rax, 1\n"
            "\tmov rdi, 1\n"
            "\tsyscall\n"
            "\tret\n"
            "_printStr:\n"
            "\txor r12, r12\n"
            "_printStrLoop:\n"
            "\tpush rax\n"
            "\tlea rsi, [rax + r12]\n"
            "\tmov rdx, 1\n"
            "\tcall _printChar\n"
            "\tpop rax\n"
            "\tadd r12, 1\n"
            "\tcmp byte [rax + r12], 0\n"
            "\tjne _printStrLoop\n"
            "\tret\n"
            "_printInt:\n"
            "\tpush rbp\n"
            "\tmov rbp, rsp\n"
            "\tmov ecx, 10\n"
            "_convertInt:\n"
            "\txor rdx, rdx\n"
            "\tdiv ecx\n"
            "\tadd edx, 48\n"
            "\tsub rsp, 1\n"
            "\tmov [rsp], dl\n"
            "\ttest eax, eax\n"
            "\tjnz _convertInt\n"
            "\tmov r8, rbp\n"
            "\tsub r8, rsp\n"
            "\tmov rax, 1\n"
            "\tmov rdi, 1\n"
            "\tmov rsi, rsp\n"
            "\tmov rdx, r8\n"
            "\tSyscall\n"
            "\tadd rsp, r8\n"
            "\tpop rbp\n"
            "\tret\n"
            "_printf:\n"
            "\txor r13, r13\n"
            "\txor rbx, rbx\n"
            "_printfloop:\n"
            "\tpush rax\n"
            "\tpush _printfloopEnd\n"
            "\tcmp byte [rax + rbx], 37\n"
            "\tje _formatSpec\n"
            "\tlea rsi, [rax + rbx]\n"
            "\tmov rdx, 1\n"
            "\tjne _printChar\n"
            "_printfloopEnd:\n"
            "\tpop rax\n"
            "\tadd rbx, 1\n"
            "\tcmp byte [rax + rbx], 0\n"
            "\tjne _printfloop\n"
            "\tret\n");

    printf("1\n");
    verifyCharAlloc(dataLen, DATA_MAX_LEN, dataSec, asmData);
    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    printf("%i\n", stackPointer);
    printf("%s\n", asmData);
    //strcat(asmData, dataSec);
    //snprintf(asmData, DATA_MAX_LEN, dataSec);
    printf("3\n");
    //strcat(asmText, textSec);
    memcpy(asmText, textSec, strlen(textSec));
    
    dataLen += strlen(dataSec);
    textLen += strlen(textSec);
    printf("4\n");
}

int acg_loadInt (int intValue) {
    stackPointer += 4; // Increase the stack by the size of an integer (4)

    char text[] = 
        ("\tsub rsp, 4\n"
         "\tmov dword [rbp - %i], %i\n");

    int max = 50;
    char textSec[max];

    int size = snprintf(textSec, max, text, stackPointer, intValue);

    // this is done to prevent seg fault
    if (size > max) {
        char newTextSec[size];
        sprintf(newTextSec, text, stackPointer, intValue);
        verifyCharAlloc(textLen, TEXT_MAX_LEN, newTextSec, asmText);
        strcat(asmText, newTextSec);
        textLen += size;

    } else {
        verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);
        strcat(asmText, textSec);
        textLen += max;
    }

    return stackPointer; // Returns the current position
}

int acg_loadStr (char *strValue) {
    stackPointer += 8; // Increase the stack by the size of an integer (4)
    
    char data[] = ("\tstr_%i db `%s`, 0\n");

    int dataMax = 300;
    char dataSec[dataMax];

    int dataSize = snprintf(dataSec, dataMax, data, strIdx, strValue);

    // this is done to prevent seg fault
    if (dataSize > dataMax) {
        char newDataSec[dataSize];
        sprintf(newDataSec, data, strIdx, strValue);
        verifyCharAlloc(dataLen, DATA_MAX_LEN, newDataSec, asmData);
        strcat(asmData, newDataSec);
        dataLen += dataSize;

    } else {
        verifyCharAlloc(dataLen, DATA_MAX_LEN, dataSec, asmData);
        strcat(asmData, dataSec);
        dataLen += dataMax;
    }

    char text[] = 
        ("\tsub rsp, 8\n"
         "\tlea rax, [rel str_%i]\n"
         "\tmov dword [rbp - %i], rax\n");

    int textMax = 100;
    char textSec[textMax];

    int size = snprintf(textSec, textMax, text, strIdx, stackPointer);

    // this is done to prevent seg fault
    if (size > textMax) {
        char newTextSec[size];
        sprintf(newTextSec, text, strIdx, stackPointer);
        verifyCharAlloc(textLen, TEXT_MAX_LEN, newTextSec, asmText);
        strcat(asmText, newTextSec);
        textLen += size;

    } else {
        verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);
        strcat(asmText, textSec);
        textLen += textMax;
    }

    strIdx += 1;

    return stackPointer; // Returns the current position
}

void acg_print(int mainStack, int argIdx, int *argList) {
    int x = 0;

    char textSec[] =
        ("\tmov r8, rbp\n"
         "\tpush rbp\n"
         "\tmov rbp, rsp\n");

    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    strcat(asmText, textSec);

    textLen += strlen(textSec);

    for (int idx = 0; idx < argIdx; ++idx) {
        x += 8;
        char temp[] = 
            ("\tsub rsp, 8\n"
             "\tmov qword [rbp - %i], [r8 - %i]\n");

    
        int max = 50;
        char tempSec[max];

        int size = snprintf(tempSec, max, temp, x, argList[idx]);

        // this is done to prevent seg fault
        if (size > max) {
            char newTempSec[size];
            sprintf(newTempSec, temp, x, argList[idx]);
            verifyCharAlloc(textLen, TEXT_MAX_LEN, newTempSec, asmText);
            strcat(asmText, newTempSec);
            textLen += size;

        } else {
            verifyCharAlloc(textLen, TEXT_MAX_LEN, tempSec, asmText);
            strcat(asmText, tempSec);
            textLen += max;
        }
    }

    char textEndSec[] = 
        ("\tcall _printf\n"
         "\tsub rsp, %i\n"
         "\tpop rbp");

    int max = 50;
    char endSec[max];

    int size = snprintf(endSec, max, textEndSec, x);

    // this is done to prevent seg fault
    if (size > max) {
        char newEndSec[size];
        sprintf(newEndSec, textEndSec, x);
        verifyCharAlloc(textLen, TEXT_MAX_LEN, newEndSec, asmText);
        strcat(asmText, newEndSec);
        textLen += size;

    } else {
        verifyCharAlloc(textLen, TEXT_MAX_LEN, endSec, asmText);
        strcat(asmText, endSec);
        textLen += max;
    }

}

int acg_add (int left, int right) {
    stackPointer += 4; // Increase the stack by the size of an integer (4)

    char text[] = 
        ("\tmov eax, dword [rbp - %i]\n"
         "\tmov edx, dword [rbp - %i]\n"
         "\tadd eax, edx\n"
         "\tsub rsp, 4\n"
         "\tmov dword [rbp - %i], eax\n");

    int max = 200;
    char textSec[max];

    int size = snprintf(textSec, max, text, left, right, stackPointer);

    // this is done to prevent seg fault
    if (size > max) {
        char newTextSec[size];
        sprintf(newTextSec, text, left, right, stackPointer);
        verifyCharAlloc(textLen, TEXT_MAX_LEN, newTextSec, asmText);
        strcat(asmText, newTextSec);
        textLen += size;

    } else {
        verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);
        strcat(asmText, textSec);
        textLen += max;
    }

    return stackPointer; // Returns the current position
}

int acg_minus (int left, int right) {
    stackPointer += 4; // Increase the stack by the size of an integer (4)

    char text[] = 
        ("\tmov eax, dword [rbp - %i]\n"
         "\tmov edx, dword [rbp - %i]\n"
         "\tsub eax, edx\n"
         "\tsub rsp, 4\n"
         "\tmov dword [rbp - %i], eax\n");

    int max = 200;
    char textSec[max];

    int size = snprintf(textSec, max, text, left, right, stackPointer);

    // this is done to prevent seg fault
    if (size > max) {
        char newTextSec[size];
        sprintf(newTextSec, text, left, right, stackPointer);
        verifyCharAlloc(textLen, TEXT_MAX_LEN, newTextSec, asmText);
        strcat(asmText, newTextSec);
        textLen += size;

    } else {
        verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);
        strcat(asmText, textSec);
        textLen += max;
    }

    return stackPointer; // Returns the current position
}

int acg_times (int left, int right) {
    stackPointer += 4; // Increase the stack by the size of an integer (4)

    char text[] = 
        ("\tmov eax, dword [rbp - %i]\n"
         "\tmul dword [rbp - %i]\n"
         "\tsub rsp, 4\n"
         "\tmov dword [rbp - %i], eax\n");

    int max = 200;
    char textSec[max];

    int size = snprintf(textSec, max, text, left, right, stackPointer);

    // this is done to prevent seg fault
    if (size > max) {
        char newTextSec[size];
        sprintf(newTextSec, text, left, right, stackPointer);
        verifyCharAlloc(textLen, TEXT_MAX_LEN, newTextSec, asmText);
        strcat(asmText, newTextSec);
        textLen += size;

    } else {
        verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);
        strcat(asmText, textSec);
        textLen += max;
    }

    return stackPointer; // Returns the current position
}

int acg_div (int left, int right) {
    stackPointer += 4; // Increase the stack by the size of an integer (4)

    char text[] = 
        ("\tmov eax, dword [rbp - %i]\n"
         "\txor rdx, rdx\n"
         "\tdiv dword [rbp - %i]\n"
         "\tsub rsp, 4\n"
         "\tmov dword [rbp - %i], eax\n");

    int max = 200;
    char textSec[max];

    int size = snprintf(textSec, max, text, left, right, stackPointer);

    // this is done to prevent seg fault
    if (size > max) {
        char newTextSec[size];
        sprintf(newTextSec, text, left, right, stackPointer);
        verifyCharAlloc(textLen, TEXT_MAX_LEN, newTextSec, asmText);
        strcat(asmText, newTextSec);
        textLen += size;

    } else {
        verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);
        strcat(asmText, textSec);
        textLen += max;
    }

    return stackPointer; // Returns the current position
}

void acg_postamble () {
    char textSec[] =
        ("\tmov rax, 60\n"
         "\tmov rdi, 0\n"
         "\tsyscall\n");

    verifyCharAlloc(textLen, TEXT_MAX_LEN, textSec, asmText);

    strcat(asmText, textSec);
    textLen += strlen(textSec);
}

