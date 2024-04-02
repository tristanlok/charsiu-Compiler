#include "defs.h"
#include "data.h"

#include "ast.h"
#include "lexer.h"
#include "interpreter.h"
#include "parser.h"

// Initializing Global Variables
int Line;
int Putback;
FILE *Infile;
struct token Token;

// Initializing Functions
static void init();
int main();


// Functions
static void init() {
    Line = 1;
    Putback = '\n';
}

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
