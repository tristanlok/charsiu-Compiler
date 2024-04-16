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
    
    printf("Syntax error on line %d, token %d\n", Line, tokenValue);
    exit(1);
}

static int detAssoc(int tokenValue) {
    if (tokenValue < OP_LEN) {
        int assoc = operatorInfo[tokenValue][1];
        
        return assoc;
    }
    
    printf("Syntax error on line %d, token %d\n", Line, tokenValue);
    exit(1);
}

static struct Node *getPrimaryNode() {
    struct Node *n;

    switch (Token.tokenValue) {
        // Deals with Expressions within Parentheses by call parseExpr again
        case L_PAREN:
            lexScan(&Token);
            n = parseExpr(0);
            if (is_token(R_PAREN)) {
                printf("Syntax error on line %d. Unmatched ( \n", Line);
                exit(1);
            }
            lexScan(&Token);
            return n;
        // Creates the left node with the integer value
        case INT_VALUE:
            n = createIntLeaf(INT_VALUE, Token.intValue);
            lexScan(&Token); // Get next token
            return n;

        default:
            printf("Syntax error on line %d\n", Line);
            exit(1);
    }
}

static struct Node *parseExpr(int minPrec) { // Utilizing Precedence Climbing Parsing with Expressions
    struct Node *leftn, *rightn;

    leftn = getPrimaryNode(); // This will also deal with any parentheses creating a sub tree before returning into the left node

    int operatorTokenvalue = Token.tokenValue;

    while (is_token(SEMI) && is_token(R_PAREN) && is_token(T_EOF) && detPrec(Token.tokenValue) > minPrec) {
        // calculate precedence and associativity of current token
        lexScan(&Token);

        rightn = parseExpr(detPrec(operatorTokenvalue) + detAssoc(operatorTokenvalue)); // If Associativity is LEFT, it will add one to the precedence

        leftn = createOpNode(operatorTokenvalue, leftn, rightn);

        operatorTokenvalue = Token.tokenValue;
    }

    return leftn;

}

// Statement Parser

struct Node *print_stmt() {
    if (next_token(L_PAREN)) {
        while (!next_token(R_PAREN)) {
            // Not supposed to be here, leave for now
            if (!is_token(PLUS)) {
                break; // SYNTAX ERROR
            }

            switch (Token.tokenValue) {
                case STR_ARR: // Terminal
                    break;
                case INT_VALUE: // Terminal
                    break;
                case L_PAREN: // Non Terminal
                    lexScan(&Token);
                    return stmt();
                default:
                    break; // Parsing Error
            }
        }
    }
}

struct Node *stmt() {
    switch (Token.tokenValue) {
        case PRINT:
            return print_stmt();
        default:
            return parseExpr(0);
    }
}

// Code Parser
void parseCode() {
    struct Node *ast;

    while (!is_token(T_EOF)) {
        switch (Token.tokenValue) {
            case PRINT:
                //ast = call_print(ast);

                // determine if ast is empty or not - ie. print(); (Edge case)
                if (!detNullTree(ast)) {
                    generateExprCode(ast);
                    gen_printint();
                }

                break;

            default:
                printf("Syntax error on line %d. Token value: %d\n", Line, Token.tokenValue);
                exit(1);
        }
    }
}

