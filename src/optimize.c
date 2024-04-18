#include "defs.h"
#include "data.h"
#include "ast.h"
#include "helper.h"
#include "optimize.h"

static struct Node *optimizeExpr(struct Node *n) {
    struct Node *node;
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
            node = createIntLeaf(INT_VALUE, LIT, (((n->left)->intLit) + ((n->right)->intLit)));

            free(n->left);
            free(n->right);

            return node;

        case MINUS:
            node = createIntLeaf(INT_VALUE, LIT, (((n->left)->intLit) - ((n->right)->intLit)));

            free(n->left);
            free(n->right);

            return node;

        case TIMES:
            node = createIntLeaf(INT_VALUE, LIT, (((n->left)->intLit) * ((n->right)->intLit)));

            free(n->left);
            free(n->right);

            return node;

        case DIV:
            node = createIntLeaf(INT_VALUE, LIT, (((n->left)->intLit) / ((n->right)->intLit)));

            free(n->left);
            free(n->right);

            return node;
        
        default:
            syntax_err();
    }
}

void *optimizeCode(struct Node *n) {
    switch (n->nodeType) {
        case OP:
            if (n->left) {
                optimizeCode(n->left);
            }

            if (n->right) {
                optimizeCode(n->right);
            }
            break;
        case STMT:
            if (n->tokenValue == EXPR) {
                n->tail = optimizeExpr(n->tail);
            }
            else if (n->tail) {
                optimizeCode(n->tail);
            }
            break;
    }
}

