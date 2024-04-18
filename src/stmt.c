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
            n = createIntLeaf(INT_VALUE, LIT, Token.intValue);
            lexScan(&Token); // Get next token
            return n;
        // Creates the left node with string value
        case STR_ARR:
            n = createStrLeaf(STR_ARR, LIT, Token.str);
            lexScan(&Token);
            return n;
            
        default:
            syntax_err();
    }
}

static struct Node *parsePrintArgs(int minPrec, int *args) {
    struct Node *leftn, *rightn;

    leftn = getPrimaryNode(); // This will also deal with any parentheses creating a sub tree before returning into the left node

    while (!is_token(R_PAREN) && 1 > minPrec) {
        if (!is_token(COMMA)) {
            missing_err(",");
        }

        // calculate precedence and associativity of current token
        lexScan(&Token);

        args -= 1;

        rightn = parsePrintArgs(2, args); // If Associativity is LEFT, it will add one to the precedence

        leftn = createOpNode(COMMA, OP, leftn, rightn);
        
    }

    return leftn;
}

struct Node *print_stmt() {
    struct Node *n = createStmtNode(PRINT, STMT, Token.str, NULL);
    if (next_token(L_PAREN)) {
        if (next_token(STR_ARR)) {
            int args = Token.args;
            n->tail = parsePrintArgs(0, &args);
            if (args != 0) {
                printf("Too little or Too many arguments presented to print");
                exit(1);
            }
        if (!is_token(R_PAREN)) {
            missing_err(")");
        }
        lexScan(&Token);
        return n;

    } else {
        missing_err("(");
    }
}
