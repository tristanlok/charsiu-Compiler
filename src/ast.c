#include "defs.h"
#include "ast.h"

static struct Node *createNode() {
    return ((struct Node*) malloc(sizeof(struct Node))); // dynamically create an object in the heap (c - malloc is c++ new)
}

struct Node *createOpNode(int tokenValue, struct Node *left, struct Node *right) {
    struct Node *n = createNode();

    n->tokenValue = tokenValue;
    n->left = left;
    n->right = right;

    return n;
}

struct Node *createIntLeaf(int tokenValue, int intValue) {
    struct Node *n = createNode();

    n->tokenValue = tokenValue;
    n->intLit = intValue;

    return n;
}

struct Node *createStrLeaf(int tokenValue, char *str) {
    struct Node *n = createNode();

    n->tokenValue = tokenValue;
    n->strLit = str;

    return n;
}

struct Node *createStrNode(int tokenValue, char *str, struct Node *tail) {
    struct Node *n = createNode();

    n->tokenValue = tokenValue;
    n->strPointer = str;
    n->strTail = tail;

    return n;
}

struct Node *createStmtNode(int tokenValue, struct Node *tail) {
    struct Node *n = createNode();

    n->tokenValue = tokenValue;
    n->tail = tail;

    return n;
}
