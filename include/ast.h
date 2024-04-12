#ifndef AST_H
#define AST_H

struct ASTnode *createNode(int tokenValue, struct ASTnode *left, struct ASTnode *right, int intValue);

struct ASTnode *createLeaf(int tokenValue, int intValue);

struct ASTnode *createSingle(int tokenValue, struct ASTnode *left, int intValue);

int detNullTree(struct ASTnode *n);

#endif
