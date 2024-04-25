#ifndef GENERATECODE_H
#define GENERATECODE_H

static void verifyAlloc (int currLen, int maxLen, int *src);

void *generateCode(struct Node *n);
int generateExprCode(struct Node *n);

void combineCode();

void gen_preamble();
void gen_postamble();
void gen_printint();

#endif
