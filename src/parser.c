#include "ast.h"
#include "data.h"
#include "lexer.h"
#include "defs.h"

static int operatorPrecedence[] = { 10, 10, 20, 20, 0, 0};
//                                  +  -   *  /  INTLIT EOF

// Ensures that the correct grammar syntax is used
static int determinePrecedence(int tokenValue) {
    int prec = operatorPrecedence[tokenValue];

    if (prec == 0){
        printf("syntax error on line %d, token %d\n", Line, tokenValue);
        exit(1);
    }

    return prec;
}

int convertToken(int tokenValue) {
    switch (tokenValue) {
        case T_PLUS:
            return N_PLUS;
        case T_MINUS:
            return N_MINUS;
        case T_TIMES:
            return N_TIMES;
        case T_DIV:
            return N_DIV;
        case T_LPAREN:
            return N_LPAREN;
        case T_RPAREN:
            return N_RPAREN;
        case T_HAT:
            return N_HAT;
        default:
            printf("Unknown token in on line %d\n", Line);
            exit(1);
    }
}

static struct ASTnode *getPrimaryNode() {
    struct ASTnode *n;

    switch (Token.tokenValue) {
        case T_INTLIT:
            n = createLeaf(T_INTLIT, Token.intValue);
            scanChar(&Token); // Get next token
            return n;

        default:
            printf("Syntax error on line %d\n", Line);
            exit(1);
    }
}

static struct ASTnode *parseExpr(int prevTokPrec) { // Utilizing Precedence Climbing Parsing with Expressions
    struct ASTnode *leftn, *rightn;

    int nodeValue;

    leftn = getPrimaryNode();

    int operatorTokenvalue = Token.tokenValue;

    while (Token.tokenValue != T_EOF && determinePrecedence(operatorTokenvalue) > prevTokPrec) {
        scanChar(&Token);

        rightn = parseExpr(determinePrecedence(operatorTokenvalue));

        leftn = createNode(convertToken(operatorTokenvalue), leftn, rightn, 0);

        operatorTokenvalue = Token.tokenValue;
    }

    return leftn;

}

struct ASTnode *makeTree(int prevTokPrec) { // For later with the introduction of recursive descent parsers for functions
    return parseExpr(prevTokPrec);
}

