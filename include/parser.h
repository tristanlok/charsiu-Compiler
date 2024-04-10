#ifndef PARSER_H
#define PARSER_H

static int determinePrecedence(int tokenValue);

int convertToken(int tokenValue);

static struct ASTnode *getPrimaryNode();

static struct ASTnode *parseExpr(int prevTokPrec);

struct ASTnode *makeTree(int prevTokPrec);

#endif
