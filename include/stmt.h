#ifndef STMT_H
#define STMT_H

static struct Node *getPrimaryNode();

static struct Node *parsePrintExpr(int minPrec);

struct Node *print_stmt();

#endif
