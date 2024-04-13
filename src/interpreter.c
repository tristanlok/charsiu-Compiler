#include "ast.h"
#include "data.h"
#include "interpreter.h"
#include "defs.h"

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
        case PLUS:
            return (leftValue + rightValue);

        case MINUS:
            return (leftValue - rightValue);

        case TIMES:
            return (leftValue * rightValue);

        case DIV:
            return (leftValue / rightValue);
        
        case INT_VALUE:
            return n->intValue;

        default:
            printf("Unknown token in on line %d\n", Line);
            exit(1);
    }
}
