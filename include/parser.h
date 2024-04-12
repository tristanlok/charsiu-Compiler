#ifndef PARSER_H
#define PARSER_H

// For Associativity
enum {
    RIGHT, LEFT
};

#define OP_LEN 4

// Must be separated by 2 to account for associative (+1)
static int operatorInfo[OP_LEN][2] = {
{1, LEFT}, // +
{1, LEFT}, // -
{3, LEFT}, // *
{3, LEFT}, // /
};

static int detPrec(int tokenValue);

static int detAssoc(int tokenValue);

int convertToken(int tokenValue);

static struct ASTnode *getPrimaryNode();

static struct ASTnode *parseExpr(int minPrec);

struct ASTnode *makeTree(int prevTokPrec);

#endif
