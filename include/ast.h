#ifndef AST_H
#define AST_H

static struct Node *createNode();

struct Node *createOpNode(int tokenValue, struct Node *left, struct Node *right);

struct Node *createIntLeaf(int tokenValue, int intValue);

struct Node *createStrLeaf(int tokenValue, char *str);

struct Node *createStmtNode(int tokenValue, struct Node *tail);

#endif
