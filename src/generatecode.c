#include "defs.h"
#include "data.h"
#include "generatecode.h"
#include "acg.h"
#include "helper.h"

// REMEMBER TO FREE ALL MALLOC

static void verifyAlloc (int currLen, int maxLen, int *src) {
    if (currLen + 1 > maxLen) {
        src = realloc(src, sizeof(int) * (currLen + 1 + maxLen));
    }
}

// Basically identical to the basic interpreter code
int generateExprCode(struct Node *n) {
    int stack, lStack, rStack;
    // Generate the code under the left most node first
    if (n->left){
        lStack = generateExprCode(n->left);
    }

    // Generate the code under the right most node
    if (n->right){
        lStack = generateExprCode(n->right);
    }

    switch (n->tokenValue) { 
        case PLUS:
            stack = acg_add(lStack, rStack);
            break;

        case MINUS:
            stack = acg_minus(lStack, rStack);
            break;

        case TIMES:
            stack = acg_times(lStack, rStack);
            break;

        case DIV:
            stack = acg_div(lStack, rStack);
            break;
        
        case INT_VALUE:
            stack = acg_loadInt(n->intLit);
            break;

        default:
            syntax_err();
    }

    return stack;
}

void *generateCode(struct Node *n) {
    int stack;
    // If it is a Node, so it goes to the bottom and works up
    switch (n->nodeType) {
        case OP:
            if (n->left) {
                generateCode(n->left);
            }

            if (n->right) {
                generateCode(n->right);
            }
            break;
        case STMT:
            if (n->tokenValue == EXPR) {
                stack = generateExprCode(n->tail);
            }
            else if (n->tail) {
                generateCode(n->tail);
            }
            break;
    }

    // If it is a leaf or statement
    switch (n->tokenValue) {
        case PRINT:
            stack = acg_loadStr(n->str);
            acg_print(stack, argIdx, argList); // requires main string + arg num + arg list
            break;

        case INT_VALUE:
            stack = acg_loadInt(n->intLit);
            break;

        case STR_ARR:
            stack = acg_loadStr(n->strLit);
            break;
    }

    // verify and add args
    verifyAlloc(argIdx, MAX_ARG, argList);
    argList[argIdx] = stack;
    argIdx += 1;
}

void gen_preamble() {
    acg_preamble();
}

void gen_postamble() {
    acg_postamble();
}

void gen_printint() {
    acg_printInt();
}

void combineCode() {
    fputs(asmData, Outfile);
    fputs(asmBss, Outfile);
    fputs(asmText, Outfile);
}

// Print requirements
//
// ability to print escape sequences (in assembly)
//
