#include "defs.h"
#include "data.h"
#include "helper.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"

static struct Node *getPrimaryNode() {
    struct Node *n;

    switch (Token.tokenValue) {
        // Deals with Expressions within Parentheses by call parseExpr again
        case L_PAREN:
            lexScan(&Token);
            n = stmt();
            if (!is_token(R_PAREN)) {
                missing_err(")");
            }
            lexScan(&Token);
            return n;
        // Creates the left node with integer value
        case INT_VALUE:
            n = createIntLeaf(INT_VALUE, Token.intValue);
            lexScan(&Token); // Get next token
            return n;
        // Creates the left node with string value
        case STR_ARR:
            n = createStrLeaf(STR_ARR, Token.strPointer);
            lexScan(&Token);
            return n;
            
        default:
            syntax_err();
    }
}

static struct Node *parsePrintExpr(int minPrec) {
    struct Node *leftn, *rightn;

    leftn = getPrimaryNode(); // This will also deal with any parentheses creating a sub tree before returning into the left node

    while (!is_token(R_PAREN) && 1 > minPrec) {
        if (!is_token(PLUS)) {
            missing_err("+");
        }

        // calculate precedence and associativity of current token
        lexScan(&Token);

        rightn = parsePrintExpr(2); // If Associativity is LEFT, it will add one to the precedence

        leftn = createOpNode(PLUS, leftn, rightn);
        
    }

    return leftn;
}

struct Node *print_stmt() {
    struct Node *n = createStmtNode(PRINT, NULL);
    if (next_token(L_PAREN)) {
        n->tail = parsePrintExpr(0);
        if (!is_token(R_PAREN)) {
            missing_err(")");
        }
        lexScan(&Token);
        return n;

    } else {
        missing_err("(");
    }
}
