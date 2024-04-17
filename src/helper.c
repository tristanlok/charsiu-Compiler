#include "defs.h"
#include "data.h"
#include "helper.h"
#include "lexer.h"


// Helper Functions

// Create Expected Error Function

int next_token(int tokenValue) {
    lexScan(&Token);
    return is_token(tokenValue);
}

int is_token(int tokenValue) {
    if (Token.tokenValue == tokenValue) {
        return 1;
    }
    return 0;
}

void syntax_err() {
    printf("Syntax error on line %d. Token value: %d\n", Line, Token.tokenValue);
    exit(1);
}

void missing_err(char *str) {
    printf("Syntax error on line %d. Expected [%s] missing\n", Line, str);
    exit(1);
}
