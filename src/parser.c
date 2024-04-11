#include "parser.h"
#include "ast.h"
#include "data.h"
#include "lexer.h"
#include "defs.h"

// Ensures that the correct grammar syntax is used
static int detPrec(int tokenValue) {
    int prec = operatorInfo[tokenValue][0];

    if (prec == 0){
        printf("syntax error on line %d, token %d\n", Line, tokenValue);
        exit(1);
    }

    return prec;
}

static int detAssoc(int tokenValue) {
    int assoc = operatorInfo[tokenValue][1];

    return assoc;
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
        default:
            printf("Unknown token in on line %d\n", Line);
            exit(1);
    }
}

static struct ASTnode *getPrimaryNode() {
    struct ASTnode *n;

    switch (Token.tokenValue) {
        // Deals with Expressions within Parentheses by call parseExpr again
        case T_LPAREN:
            scanChar(&Token);
            n = parseExpr(0);
            if (Token.tokenValue != T_RPAREN) {
                printf("Syntax error on line %d. Unmatched ( \n", Line);
                exit(1);
            }
            scanChar(&Token);
            return n;
        // Creates the left node with the integer value
        case T_INTLIT:
            n = createLeaf(T_INTLIT, Token.intValue);
            scanChar(&Token); // Get next token
            return n;

        default:
            printf("Syntax error on line %d\n", Line);
            exit(1);
    }
}

static struct ASTnode *parseExpr(int minPrec) { // Utilizing Precedence Climbing Parsing with Expressions
    struct ASTnode *leftn, *rightn;

    leftn = getPrimaryNode(); // This will also deal with any parentheses creating a sub tree before returning into the left node

    int operatorTokenvalue = Token.tokenValue;

    while (Token.tokenValue != T_RPAREN && Token.tokenValue != T_EOF && detPrec(Token.tokenValue) > minPrec) {
        // calculate precedence and associativity of current token
        
        scanChar(&Token);

        rightn = parseExpr(detPrec(operatorTokenvalue) + detAssoc(operatorTokenvalue)); // If Associativity is LEFT, it will add one to the precedence

        leftn = createNode(convertToken(operatorTokenvalue), leftn, rightn, 0);

        operatorTokenvalue = Token.tokenValue;
    }

    return leftn;

}

struct ASTnode *makeTree(int prevTokPrec) { // For later with the introduction of recursive descent parsers for functions
    return parseExpr(prevTokPrec);
}

