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

struct ASTnode *print_stmt() {
    if (next_token(L_PAREN)) {
        

}
