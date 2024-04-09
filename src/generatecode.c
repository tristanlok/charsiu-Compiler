#include "acg.h"
#include "defs.h"
#include "data.h"
#include "generatecode.h"

// Basically identical to the basic interpreter code
static int generate(struct ASTnode *n) {
    // Generate the code under the left most node first
    if (n->left){
        generate(n->left);
    }

    // Generate the code under the right most node
    if (n->right){
        generate(n->right);
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
            printf("Unknown token in on line %d\n", Line);
            exit(1);
    }
}

void generateCode(struct ASTnode *n) {
    acg_preamble();
    generate(n);

    acg_printInt();
    acg_postamble();
}
