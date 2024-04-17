#include "defs.h"
#include "data.h"
#include "generatecode.h"
#include "acg.h"

// Basically identical to the basic interpreter code
void generateCode(struct Node *n) {
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
            if ((n->left)->tokenValue == INT_VALUE && (n->right)->tokenValue == INT_VALUE) {
                acg_addInt();
            } else {
                acg_addStr();
            }
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
            acg_loadInt(n->intValue);
            break;

        case STR_ARR:
            acg_loadStr(n->strPointer);

        default:
            printf("Unknown token in on line %d. Token value: %d\n", Line, n->tokenValue);
            exit(1);
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

// Print requirements
//
// ability to print escape sequences (in assembly)
//
