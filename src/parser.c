#include "parser.h"
#include "ast.h"
#include "data.h"
#include "generatecode.h"
#include "lexer.h"
#include "defs.h"
#include "helper.h"
#include "stmt.h"


// Expression Parser

// Ensures that the correct grammar syntax is used
static int detPrec(int tokenValue) {
    if (tokenValue < OP_LEN) {
        int prec = operatorInfo[tokenValue][0];
        
        return prec;
    }
    
    syntax_err();
}

static int detAssoc(int tokenValue) {
    if (tokenValue < OP_LEN) {
        int assoc = operatorInfo[tokenValue][1];
        
        return assoc;
    }
    
    syntax_err();
}

static struct Node *getExprNode() {
    struct Node *n;

    switch (Token.tokenValue) {
        // Deals with Expressions within Parentheses by call parseExpr again
        case L_PAREN:
            lexScan(&Token);
            n = parseExpr(0);
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

        default:
            syntax_err();
    }
}

static struct Node *parseExpr(int minPrec) { // Utilizing Precedence Climbing Parsing with Expressions
    struct Node *leftn, *rightn;

    leftn = getExprNode(); // This will also deal with any parentheses creating a sub tree before returning into the left node

    int operatorTokenvalue = Token.tokenValue;

    while (!is_token(COMMA) && !is_token(R_PAREN) && detPrec(Token.tokenValue) > minPrec) {
        // calculate precedence and associativity of current token
        lexScan(&Token);

        rightn = parseExpr(detPrec(operatorTokenvalue) + detAssoc(operatorTokenvalue)); // If Associativity is LEFT, it will add one to the precedence

        leftn = createOpNode(operatorTokenvalue, OP, leftn, rightn);

        operatorTokenvalue = Token.tokenValue;
    }

    return leftn;
}

// Statement Parser
struct Node *stmt() {
    switch (Token.tokenValue) {
        case PRINT:
            return print_stmt();
        default:
            return createStmtNode(EXPR, STMT, NULL, parseExpr(0));
    }
}

// Code Parser
void parseCode() {
    struct Node *n;

    while (!is_token(T_EOF)) {
        n = stmt();

    }
}

