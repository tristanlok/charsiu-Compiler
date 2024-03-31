#ifndef PARSER_H
#define PARSER_H

static int determinePrecedence(int tokenValue);

int convertToken(int tokenValue);

static struct ASTnode *getPrimaryNode();

struct ASTnode *makeTree(int prevTokPrec);

#endif