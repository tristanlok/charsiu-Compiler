#include "defs.h"
#include "data.h"
#include "ast.h"
#include "helper.h"
#include "optimize.h"

struct Node *optimizeExpr(struct Node *n) {
    // Generate the code under the left most node first
    if ((n->left)->tokenValue != INT_VALUE) {
        n->left = optimizeExpr(n->left);
    }

    // Generate the code under the right most node
    if ((n->right)->tokenValue != INT_VALUE) {
        n->right = optimizeExpr(n->right);
    }

    switch (n->tokenValue) { 
        case PLUS:
            return createIntLeaf(INT_VALUE, (((n->left)->intLit) + ((n->right)->intLit)));

        case MINUS:
            return createIntLeaf(INT_VALUE, (((n->left)->intLit) - ((n->right)->intLit)));

        case TIMES:
            return createIntLeaf(INT_VALUE, (((n->left)->intLit) * ((n->right)->intLit)));

        case DIV:
            return createIntLeaf(INT_VALUE, (((n->left)->intLit) / ((n->right)->intLit)));
        
        default:
            syntax_err();
    }
}

