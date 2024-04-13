#include "ast.h"
#include "defs.h"

struct ASTnode *createExprNode(int tokenValue, struct ASTnode *left, struct ASTnode *right, int intValue) {
    struct ASTnode *node;

    node = (struct ASTnode*) malloc(sizeof(struct ASTnode)); // dynamically create an object in the heap (c - malloc is c++ new)

    node->tokenValue = tokenValue;
    node->left = left;
    node->right = right;
    node->intValue = intValue;

    return node;
}

struct ASTnode *createExprLeaf(int tokenValue, int intValue) {
    return createExprNode(tokenValue, NULL, NULL, intValue);
}

struct ASTnode *createExprSingle(int tokenValue, struct ASTnode *left, int intValue) {
    return createExprNode(tokenValue, left, NULL, intValue);
}

int detNullTree(struct ASTnode *n) {
    if (n->tokenValue == 0 && n->left == NULL && n->right == NULL && n->intValue == 0) {
        return 1;
    }
    return 0;
}
