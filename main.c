#include "Header_Files\\ast.h"
#include "Header_Files\\lexer.h"
#include "Header_Files\\defs.h"
#include "Header_Files\\interpreter.h"
#include "Header_Files\\parser.h"

#include "Header_Files\\data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int Line;
int Putback;
FILE *Infile;
struct token Token;

static void init();

static void init() {
    Line = 1;
    Putback = '\n';
}

int main();

int main() {
    struct ASTnode *n;

    init();

    char path[20];

    printf("Please input the path to the code: ");
    scanf("%s", path);

    Infile = fopen(path, "r");

    scanChar(&Token);
    n = makeTree(0);

    printf("%d\n", interpretTree(n));

    return 0;
}
