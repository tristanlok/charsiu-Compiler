#ifndef PARSER_H
#define PARSER_H

int convertToken(int tokenValue);

static struct ASTnode *getPrimaryNode();

struct ASTnode *makeTree();

#endif