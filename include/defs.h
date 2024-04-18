#ifndef DEFS_H
#define DEFS_H

#define IDENT_MAX_LEN 512 // defines the constant max length of an identifier
#define STR_MAX_LEN 2048 // defines the max length of strings to be 512 characters

#define DATA_MAX_LEN 1028
#define BSS_MAX_LEN 1028
#define TEXT_MAX_LEN 4096

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

// TOKEN

// Token Type
enum {
    // Single-Character Tokens
    PLUS, MINUS, TIMES, DIV, SEMI, L_PAREN, R_PAREN, COMMA,

    // Literals
    IDENTIFIER, INT_VALUE, STR_ARR,

    // Keywords
    EXPR, PRINT,


    T_EOF
};

struct token{
    int tokenValue;
    union {
        int intValue;
        
        struct {
            char *str;
            int args;
        };
    };
};

//ABSTRACT SYNTAX TREE

enum {
    OP, LIT, STMT
};

struct Node{
    int tokenValue;
    int nodeType;

    union {
        // Binary Operators
        struct {
            struct Node *left;
            struct Node *right;
        };

        // Statement
        struct {
            char *str;
            struct Node *tail;
        };

        // Integer Lit
        int intLit;

        // String Lit
        char *strLit;
    };
};

#endif
