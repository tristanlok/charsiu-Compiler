#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum {
  PLUS, MINUS, TIMES, DIV, INTLIT
};

struct token {
    int token;
    int intValue;
};


#endif