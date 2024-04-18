#ifndef AST_H
#define AST_H

static struct Node *createNode();

struct Node *createOpNode(int tokenValue, int nodeType, struct Node *left, struct Node *right);
struct Node *createIntLeaf(int tokenValue, int nodeType, int intValue);
struct Node *createStrLeaf(int tokenValue, int nodeType, char *str);
struct Node *createStmtNode(int tokenValue, int nodeType, char *str, struct Node *tail);

#endif
