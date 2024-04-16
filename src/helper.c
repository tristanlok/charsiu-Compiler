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
