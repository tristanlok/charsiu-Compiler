#include "defs.h"
#include "data.h"

//#include "ast.h" Add back if needed
#include "lexer.h"
#include "interpreter.h"
#include "parser.h"
#include "generatecode.h"

// Initializing Global Variables
int Line;
int Putback;
FILE *Infile;
FILE *Outfile;
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

    // Reads the file
    Infile = fopen(path, "r");

    // Scans each token and creates an AST tree
    scanChar(&Token);
    n = makeTree(0);

    // Interprets the AST Tree
    // printf("%d\n", interpretTree(n));
    
    // Translates the AST Tree into Assembly x86-64 (NASM)
    Outfile = fopen("out.asm", "w");
    generateCode(n);
    fclose(Outfile);

    return 0;
}
