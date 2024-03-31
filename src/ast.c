#include "..\\include\\ast.h"
#include "..\\include\\defs.h"

#include <stdlib.h>

struct ASTnode *createNode(int tokenValue, struct ASTnode *left, struct ASTnode *right, int intValue) {
    struct ASTnode *node;

    node = (struct ASTnode*) malloc(sizeof(struct ASTnode)); // dynamically create an object in the heap (c - malloc is c++ new)

    node->tokenValue = tokenValue;
    node->left = left;
    node->right = right;
    node->intValue = intValue;

    return node;
}

struct ASTnode *createLeaf(int tokenValue, int intValue) {
    return createNode(tokenValue, NULL, NULL, intValue);
}

struct ASTnode *createSingle(int tokenValue, struct ASTnode *left, int intValue) {
    return createNode(tokenValue, left, NULL, intValue);
}
