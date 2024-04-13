#include "parser.h"
#include "ast.h"
#include "data.h"
#include "generatecode.h"
#include "lexer.h"
#include "defs.h"

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

static struct ASTnode *getPrimaryNode() {
    struct ASTnode *n;

    switch (Token.tokenValue) {
        // Deals with Expressions within Parentheses by call parseExpr again
        case L_PAREN:
            lexScan(&Token);
            n = parseExpr(0);
            if (Token.tokenValue != R_PAREN) {
                printf("Syntax error on line %d. Unmatched ( \n", Line);
                exit(1);
            }
            lexScan(&Token);
            return n;
        // Creates the left node with the integer value
        case INT_VALUE:
            n = createExprLeaf(INT_VALUE, Token.intValue);
            lexScan(&Token); // Get next token
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

    while (Token.tokenValue != SEMI && Token.tokenValue != R_PAREN && Token.tokenValue != T_EOF && detPrec(Token.tokenValue) > minPrec) {
        // calculate precedence and associativity of current token
        lexScan(&Token);

        rightn = parseExpr(detPrec(operatorTokenvalue) + detAssoc(operatorTokenvalue)); // If Associativity is LEFT, it will add one to the precedence

        leftn = createExprNode(operatorTokenvalue, leftn, rightn, 0);

        operatorTokenvalue = Token.tokenValue;
    }

    return leftn;

}

// Statement Parser

// Print

static struct ASTnode *call_print(struct ASTnode *tree) {
    lexScan(&Token);

    if (Token.tokenValue == L_PAREN) {
        lexScan(&Token);

        // Accounts for the edge case if print(); occurs
        if (Token.tokenValue != R_PAREN) {
            tree = parseExpr(0);
        
        } else {
            lexScan(&Token); // skip over ')'
        
            // Checks if the next token is ';'
            if (Token.tokenValue == SEMI) {
                lexScan(&Token);
                
            } else {
                printf("Syntax error on line %d. Missing ';'\n", Line);
                exit(1);
            }

            return tree;
        }
        
        if (Token.tokenValue != R_PAREN) {
            printf("Syntax error on line %d. print function missing ')'\n", Line);
            exit(1);
        }
        
        lexScan(&Token);

        if (Token.tokenValue != SEMI) {
            printf("Syntax error on line %d. Missing ';'\n", Line);
            exit(1);
        }

        lexScan(&Token);

        return tree;
    
    } else {
        printf("Syntax error on line %d. print function missing '('\n", Line);
        exit(1);
    }
}

// Code Parser

void parseCode() {
    struct ASTnode *ast = createExprNode(0, NULL, NULL, 0); // Initialize AST variable

    while (Token.tokenValue != T_EOF) {
        switch (Token.tokenValue) {
            case PRINT:
                ast = call_print(ast);

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

