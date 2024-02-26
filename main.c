#include "ast.h"
#include "lexer.h"
#include "defs.h"
#include "interpreter.h"
#include "parser.h"

#include "data.h"

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

    scanFile(&Token);
    n = makeTree();

    printf("%d\n", interpretTree(n));

    return 0;
}