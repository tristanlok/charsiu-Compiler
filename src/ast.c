#include "defs.h"
#include "ast.h"

static struct Node *createNode() {
    return ((struct Node*) malloc(sizeof(struct Node))); // dynamically create an object in the heap (c - malloc is c++ new)
}

struct Node *createOpNode(int tokenValue, struct Node *left, struct Node *right) {
    struct Node *node = createNode();

    node->tokenValue = tokenValue;
    node->left = left;
    node->right = right;

    return node;
}

struct Node *createIntLeaf(int tokenValue, int intValue) {
    struct Node *node = createNode();

    node->tokenValue = tokenValue;
    node->tokenValue = intValue;

    return node;
}

