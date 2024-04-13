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
