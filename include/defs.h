#ifndef DEFS_H
#define DEFS_H

#define IDENT_MAX_LEN 512 // defines the constant max length of an identifier
#define STR_MAX_LEN 2048 // defines the max length of strings to be 512 characters

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

// TOKEN

// Token Type
enum {
    // Single-Character Tokens
    PLUS, MINUS, TIMES, DIV, SEMI, L_PAREN, R_PAREN, 

    // Literals
    IDENTIFIER, INT_VALUE, STR_ARR,

    // Keywords
    PRINT,


    T_EOF
};

struct token{
    int tokenValue;
    union {
        int intValue;
        char *strPointer;
    };
};

//ABSTRACT SYNTAX TREE

struct Node{
    int tokenValue;

    union {
        // Binary Operators
        struct {
            struct Node *left;
            struct Node *right;
        };

        // Integer Lit
        int intValue;

        // String Lit
        char *strPointer;
    };
};

#endif
