#ifndef DEFS_H
#define DEFS_H

#define IDENT_MAX_LEN 512 // defines the constant max length of an identifier

// Token & Node Type have to match up

// TOKEN

// Token Type
enum {
  T_PLUS, T_MINUS, T_TIMES, T_DIV, T_INTLIT, T_PRINT, T_SEMI, T_LPAREN, T_RPAREN, T_EOF
};

struct token {
    int tokenValue;
    int intValue;
};


//ABSTRACT SYNTAX TREE

// Node Type
enum {
  N_PLUS, N_MINUS, N_TIMES, N_DIV, N_INTLIT
};

struct ASTnode {
  int tokenValue;
  struct ASTnode *left;
  struct ASTnode *right;
  int intValue;
};

#endif
