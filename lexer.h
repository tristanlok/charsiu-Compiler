#ifndef LEXER_H
#define LEXER_H

#include "token.h"

int scan(struct token *t);
static int chrpos(char *s, int c);
static int getint(int c);
static int skipwhitespace(void);
static int getNext(void);
static void putback(int c);

#endif