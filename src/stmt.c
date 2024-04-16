// print statement plan (PRINT + PRINTLN)
//
// DOES NOT SUPPORT CONCAT DIFFERENT DATA TYPES
//
// Determine it is the string token
//
// recursive into the print statement each time we encounter the '(' token
//
// in the function
// switch
//  - case string
//  - case integer
//  - future: case variable (string)
//  - case '('

#include "defs.h"
#include "data.h"
#include "helper.h"
#include "lexer.h"

struct ASTnode *print_stmt() {
    if (next_token(L_PAREN)) {
        while (!next_token(R_PAREN)) {
            // Not supposed to be here, leave for now
            if (!is_token(PLUS)) {
                break; // SYNTAX ERROR
            }

            switch (Token.tokenValue) {
                case STR_ARR: // Terminal
                    break;
                case INT_VALUE: // Terminal
                    break;
                case L_PAREN: // Non Terminal
                    lexScan(&Token);
                    return 
                default:
                    break; // Parsing Error
            }
        }
    }
}
