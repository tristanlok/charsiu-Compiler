#include "defs.h"
#include "data.h"
#include "generatecode.h"
#include "acg.h"

// Basically identical to the basic interpreter code
void generateExprCode(struct ASTnode *n) {
    // Generate the code under the left most node first
    if (n->left){
        generateExprCode(n->left);
    }

    // Generate the code under the right most node
    if (n->right){
        generateExprCode(n->right);
    }

    switch (n->tokenValue) { 
        case N_PLUS:
            acg_add();
            break;

        case N_MINUS:
            acg_minus();
            break;

        case N_TIMES:
            acg_times();
            break;

        case N_DIV:
            acg_div();
            break;
        
        case N_INTLIT:
            acg_load(n->intValue);
            break;

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
