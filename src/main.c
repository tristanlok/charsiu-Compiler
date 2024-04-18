#include "defs.h"
#include "data.h"

#include "lexer.h"
#include "parser.h"
#include "generatecode.h"

// Initializing Global Variables
int Line;
int Putback;
FILE *Infile;
FILE *Outfile;
struct token Token;
char identText[IDENT_MAX_LEN + 1];
char stringData[STR_MAX_LEN + 1];

// for asm
int dataLen = 0;
char *asmData = malloc(sizeof(char) * DATA_MAX_LEN);
int bssLen = 0;
char *asmBss = malloc(sizeof(char) * BSS_MAX_LEN);
int textLen = 0;
char *asmText = malloc(sizeof(char) * TEXT_MAX_LEN);

// Initializing Functions
static void init();
int main();


// Functions
static void init() {
    Line = 1;
    Putback = '\n';
}

int main() {
    struct Node *n;

    init();

    char path[20];

    printf("Please input the path to the code: ");
    scanf("%s", path);

    // Reads the file
    Infile = fopen(path, "r");

    // Translates the AST Tree into Assembly x86-64 (NASM)
    Outfile = fopen("out.asm", "w");

    lexScan(&Token);
    gen_preamble();
    parseCode();
    gen_postamble();

    fclose(Outfile);

    system("nasm -f elf64 -o out.o out.asm"); // creates object file
    system("ld out.o -o out"); // creates binary
    
    // Remove the extra files
    system("rm out.o");
    system("rm out.asm");

    return 0;
}
