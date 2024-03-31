#include "Header_Files\\ast.h"
#include "Header_Files\\data.h"
#include "Header_Files\\lexer.h"

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

/*

Parser w/ preceedence using Pratt's parser (Understanding)

1 + 4 * 7 + 3

Takes in the first int token (1)

Scan the next token - move on if not EOF

check if the current precedence is greater than the previous (+) 10 > 0

scans the next token (4)

Recursively calls itself giving the precidence of the operator (10)

Takes in the first token (4)

scan the next token - move on if not EOF

check if the current precedence is greater that the previous (x) 20 > 10

scans the next token (7)

Recursively calls itself giving hte precidence of the operator (20)

Takes in the first token (7)

scan in the next token - move on if not EOF

check if the current precedence is greater than the previous (+) 10 > 20 (false)

returns back 7 as right

creates the first subtree (multiplication 4*7)

checks if the TOKEN (currently +) 10 > 20 (false)

returns multiplcation subtree back to first function as right

creates the second subtree [1 + (4 * 7)]

checks if the TOKEN (currently +) 10 > 0

scans the next token (3)

since EOF after right will be 3

creates the third subtree [1 + (4 * 7)] + 3

since EOF

return third subtree

*/

struct ASTnode *makeTree(int prevTokPrec) {
    struct ASTnode *leftn, *rightn;
    int nodeValue;

    leftn = getPrimaryNode();

    int operatorTokenvalue = Token.tokenValue;

    while (Token.tokenValue != T_EOF && determinePrecedence(operatorTokenvalue) > prevTokPrec) {
        scanChar(&Token);

        rightn = makeTree(determinePrecedence(operatorTokenvalue));

        leftn = createNode(convertToken(operatorTokenvalue), leftn, rightn, 0);

        operatorTokenvalue = Token.tokenValue;
    }

    return leftn;

}
