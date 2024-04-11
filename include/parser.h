#ifndef PARSER_H
#define PARSER_H

// For Associativity
enum {
    RIGHT, LEFT
};

// Must be separated by 2 to account for associative (+1)
static int operatorInfo[7][2] = {
{1, LEFT}, // +
{1, LEFT}, // -
{3, LEFT}, // *
{3, LEFT}, // /
{5, RIGHT},// ^
{0, 0},    // INTLIT
{0, 0}     // EOF
};

static int detPrec(int tokenValue);

static int detAssoc(int tokenValue);

int convertToken(int tokenValue);

static struct ASTnode *getPrimaryNode();

static struct ASTnode *parseExpr(int minPrec);

struct ASTnode *makeTree(int prevTokPrec);

#endif
