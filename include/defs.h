#ifndef DEFS_H
#define DEFS_H

// TOKEN

// Token Type
enum {
  T_PLUS, T_MINUS, T_TIMES, T_DIV, T_LPAREN, T_RPAREN, T_HAT, T_INTLIT, T_EOF
};

struct token {
    int tokenValue;
    int intValue;
};


//ABSTRACT SYNTAX TREE

// Node Type
enum {
  N_PLUS, N_MINUS, N_TIMES, N_DIV, N_LPAREN, N_RPAREN, N_HAT, N_INTLIT
};

struct ASTnode {
  int tokenValue;
  struct ASTnode *left;
  struct ASTnode *right;
  int intValue;
};

// Parser Info

// For Associativity
enum {
    LEFT, RIGHT, NONE
};

#endif
