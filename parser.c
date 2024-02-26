#include "ast.h"
#include "data.h"
#include "lexer.h"

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
            scanFile(&Token); // Get next token
            return n;

        default:
            printf("Syntax error on line %d\n", Line);
            exit(1);
    }
}

/*

Simple Parser w/o priorities

5 + 5

Gets the first number -> 5 as left then it scans the next one

It gets the node value of the second one, +

it then scans the next token

it then recursively calls upon itself, if the left is the last thing, it returns that leaf as the right else, you get it to work recursively

now it builds a tree with both leafs with the head being the +

*/

struct ASTnode *makeTree() {
    struct ASTnode *n, *leftn, *rightn;
    int nodeValue;

    leftn = getPrimaryNode();

    if (Token.tokenValue == T_EOF) {
        return leftn;
    }

    nodeValue = convertToken(Token.tokenValue);

    scanFile(&Token);

    rightn = makeTree();

    n = createNode(nodeValue, leftn, rightn, 0); // creates the node with the operator as the head

    return n;

}