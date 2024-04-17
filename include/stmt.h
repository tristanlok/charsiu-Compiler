#ifndef STMT_H
#define STMT_H

static struct Node *getPrimaryNode();

static struct Node *parsePrintArgs(int minPrec, int *args);

struct Node *print_stmt();

#endif
