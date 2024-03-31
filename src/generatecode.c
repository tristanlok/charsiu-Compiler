#include "..\\include\\generatecode.h"
#include "..\\include\\defs.h"
#include "..\\include\\data.h"
#include "..\\include\\acg.h"

// Basically identical to the basic interpreter code
static int generate (struct ASTnode *n) {
    int leftReg, rightReg;

    // Generate the code under the left most node first
    if (n->left){
        leftReg = generate(n->left);
    }

    // Generate the code under the right most node
    if (n->right){
        rightReg = generate(n->right);
    }

    switch (n->tokenValue) { 
        case N_PLUS:
            return acg_add(leftReg, rightReg);

        case N_MINUS:
            return acg_minus(leftReg, rightReg);

        case N_TIMES:
            return acg_times(leftReg, rightReg);

        case N_DIV:
            return acg_div(leftReg, rightReg);
        
        case N_INTLIT:
            return acg_load(n->intValue);

        default:
            printf("Unknown token in on line %d\n", Line);
            exit(1);
    }
}

void generateCode(struct ASTnode *n) {
    int reg;

    acg_preamble();
    reg = generate(n);

    acg_printInt(reg);
    acg_postamble();
}
