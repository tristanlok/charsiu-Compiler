#include "lexer.h"
#include "token.h"

#define extern_
#include "data.h"
#undef extern_

static void init();

static void init() {
    Line = 1;
    Putback = '\n';
}

static void scanfile();

static void scanfile() {
    struct token T;

    char *tokenEnglish[5] = { "+", "-", "*", "/", "intlit" };

    while (scan(&T)) {
        printf("Token %s", tokenEnglish[T.token]);
        if (T.token == INTLIT) {
            printf(", value %d\n", T.intValue);
        }
    }
}

int main();

int main() {

    init();

    char path[20];

    printf("Please input the path to the code: ");
    scanf("%s", path);

    Infile = fopen(path, "r");

    scanfile();

    return 0;
}