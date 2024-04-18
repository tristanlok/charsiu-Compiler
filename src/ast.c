#include "defs.h"
#include "ast.h"

static struct Node *createNode() {
    return ((struct Node*) malloc(sizeof(struct Node))); // dynamically create an object in the heap (c - malloc is c++ new)
}

struct Node *createOpNode(int tokenValue, int nodeType, struct Node *left, struct Node *right) {
    struct Node *n = createNode();

    n->tokenValue = tokenValue;
    n->nodeType = nodeType;
    n->left = left;
    n->right = right;

    return n;
}

struct Node *createIntLeaf(int tokenValue, int nodeType, int intValue) {
    struct Node *n = createNode();

    n->tokenValue = tokenValue;
    n->nodeType = nodeType;
    n->intLit = intValue;

    return n;
}

struct Node *createStrLeaf(int tokenValue, int nodeType, char *str) {
    struct Node *n = createNode();

    n->tokenValue = tokenValue;
    n->nodeType = nodeType;
    n->strLit = str;

    return n;
}

struct Node *createStmtNode(int tokenValue, int nodeType, char *str, struct Node *tail) {
    struct Node *n = createNode();

    n->tokenValue = tokenValue;
    n->nodeType = nodeType;
    n->str = str;
    n->tail = tail;

    return n;
}
