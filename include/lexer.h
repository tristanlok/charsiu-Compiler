#ifndef LEXER_H
#define LEXER_H

static int chrpos(char *s, int c);
static int getint(int c);
static int skipwhitespace(void);
static int getNext(void);
static void putback(int c);
static int detKeyword ();
static int scanIdentifier (int c);
int lexScan(struct token *t);

#endif
