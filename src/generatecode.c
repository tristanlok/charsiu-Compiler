#include "defs.h"
#include "data.h"
#include "generatecode.h"
#include "acg.h"
#include "helper.h"

// REMEMBER TO FREE ALL MALLOC

// Basically identical to the basic interpreter code
void generateExprCode(struct Node *n) {
    // Generate the code under the left most node first
    if (n->left){
        generateCode(n->left);
    }

    // Generate the code under the right most node
    if (n->right){
        generateCode(n->right);
    }

    switch (n->tokenValue) { 
        case PLUS:
            acg_add();
            break;

        case MINUS:
            acg_minus();
            break;

        case TIMES:
            acg_times();
            break;

        case DIV:
            acg_div();
            break;
        
        case INT_VALUE:
            acg_loadInt(n->intLit);
            break;

        default:
            syntax_err();
    }
}

void *generateCode(struct Node *n) {
    switch (n->nodeType) {
        case OP:
            if (n->left) {
                generateCode(n->left);
            }

            if (n->right) {
                generateCode(n->right);
            }
            break;
        case STMT:
            if (n->tokenValue == EXPR) {
                generateExprCode(n->tail);
            }
            else if (n->tail) {
                generateCode(n->tail);
            }
            break;
    }

    switch (n->tokenValue) {
        case PRINT:
            acg_loadData(n->str);
            acg_print();
            break;

        case COMMA:
            break;

        case INT_VALUE:
            acg_loadInt(n->intLit);
            break;

        case STR_ARR:
            acg_loadStr(n->strLit);
            break;
    }
}

void gen_preamble() {
    acg_preamble();
}

void gen_postamble() {
    acg_postamble();
}

void gen_printint() {
    acg_printInt();
}

void combineCode() {
    fputs(asmData, Outfile);
    fputs(asmBss, Outfile);
    fputs(asmText, Outfile);
}

// Print requirements
//
// ability to print escape sequences (in assembly)
//
