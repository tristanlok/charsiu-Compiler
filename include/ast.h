#ifndef AST_H
#define AST_H

struct ASTnode *createExprNode(int tokenValue, struct ASTnode *left, struct ASTnode *right, int intValue);

struct ASTnode *createExprLeaf(int tokenValue, int intValue);

struct ASTnode *createExprSingle(int tokenValue, struct ASTnode *left, int intValue);

int detNullTree(struct ASTnode *n);

#endif
