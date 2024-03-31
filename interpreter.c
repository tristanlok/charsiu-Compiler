#include "Header_Files\\ast.h"
#include "Header_Files\\data.h"

int interpretTree(struct ASTnode *n) {

    int leftValue, rightValue;

    // If left is not a leaf
    if (n->left) {
        leftValue = interpretTree(n->left); // Recursive to the next node under left
    }

    // If right is not a leaf
    if (n->right) {
        rightValue = interpretTree(n->right); // Recursive to the next node under right
    }

    switch (n->tokenValue) {
        case N_PLUS:
            return (leftValue + rightValue);

        case N_MINUS:
            return (leftValue - rightValue);

        case N_TIMES:
            return (leftValue * rightValue);

        case N_DIV:
            return (leftValue / rightValue);
        
        case N_INTLIT:
            return n->intValue;

        default:
            printf("Unknown token in on line %d\n", Line);
            exit(1);
    }
}
