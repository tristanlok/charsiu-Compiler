#include "defs.h"
#include "data.h"
#include "lexer.h"

static void putback(int c) {
  Putback = c;
}

static int getNext(void){
    int c;

    if (Putback){ // If there is putback, read that instead of the next character in line
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    //printf("%c, %d\n", c, c); // KEEP THIS FOR TESTING
    
    if (c == '\n'){
        Line++;
    }
    return c;
}

static int skipwhitespace(void) {
    int c;

    c = getNext();
    while (c == ' ' || c == '\t' || c == '\n' || c== '\r' || c == '\f') {
        c = getNext();
    }
    return c;
}

static int detInt(char *s, int c) { // s - list of integers | c - ascii of integer
    char *r;

    r = strchr(s, c);

    if (r) {
        return r - s;
    } else {
        return -1;
    }
}

static int getint(int c) {
    int i, val = 0;

    while ((i = detInt("0123456789", c)) >= 0) { // Construct the integer
        val = val * 10 + i;
        c = getNext();
    }

    // Puts back the last character (as it is not an integer)
    putback(c);
    return val;
}

// there is no need to clear identText before comparing as strcmp compares until != or reaches null terminator
static int detKeyword () {
    switch (identText[0]) { // use a switch case to optimize the search by automating the first character
        case 'p':
            if (!strcmp(identText, "print")) { // if identifier is "print"
                return PRINT;
            }
            // more can be added here later
            break; 
        // add more cases for different identifiers here later
    }
    return 0; // if identifier is not a keyword
}

// Grabs all alphanumeric Identifiers | ASCII: 65 - 90, 95,97 - 122
static int scanIdentifier (int c) {
    int idx = 0;

    while (isalpha(c) || isdigit(c) || c == '_') {
        identText[idx++] = c; // array[i++] increments the value of i. The expression evaluates to array[i], before i has been incremented.

        c = getNext(); // get next character
                       //
        if (IDENT_MAX_LEN == idx) {
            printf("Identifier has exceeded the %d character limit, Line %d\n", IDENT_MAX_LEN, Line);
            exit(1);
        }
    }

    // Putback the last character since it is not valid
    putback(c);
    
    // Make the last character in the buffer a null terminator
    identText[idx] = '\0';

    return idx; // return the length of identifier
}

// Add to header file
static int getStr(int max, int symbol, int *args) {
    int size = 0;
    int c = getNext(); // Grabs the next character
    int escapeChr = 0;

    while (c != symbol) {
        if (c == '\n') {
            printf("Syntax error, Missing closing quotation, line %d\n", Line);
            exit(1);
        }

        if (c == 92) { // Does c == \ (Escape Sequence)
            c = getNext();
            
            // case for supported escape sequences
            if (c == 'n' || c == 't' || c == 92 || c == 34 || c == 39 || c == '?') {
                stringData[size++] = 92; // add \ into string
                escapeChr += 1;

            } else {
                printf("Unsupported Escape Sequence on line %d\n", Line);
                exit(1);
            }
        
        } else if (c == '%') {
            c = getNext();
            
            stringData[size++] = '%';

            if (c == 'i' || c == 's') {
                args += 1;
            }
        }

        stringData[size++] = c;

        c = getNext();

        if (max == size) {
            printf("String has exceeded the %d character limit, Line %d\n", max, Line);
            exit(1);
        }
    }

    c = getNext(); // Moves past the Quotation mark

    return (size - escapeChr); // Escape Sequences count as 1 character
}

int lexScan(struct token *t) {
    int c;

    c = skipwhitespace(); // get the next character that is not a whitespace

    switch (c) {
        case EOF:
            t->tokenValue = T_EOF;
            break;
        case '+':
            t->tokenValue = PLUS;
            break;
        case '-':
            t->tokenValue = MINUS;
            break;
        case '*':
            t->tokenValue = TIMES;
            break;
        case '/':
            t->tokenValue = DIV;
            break;
        case '(':
            t->tokenValue = L_PAREN;
            break;
        case ')':
            t->tokenValue = R_PAREN;
            break;
        case ',':
            t->tokenValue = COMMA;
            break;
        case ';':
            t->tokenValue = SEMI;
            break;
        case 39: { // ASCII for '
            t->tokenValue = STR_ARR;

            int args = 0;
            
            int size = getStr(1, 39, &args);

            char tempString[size];

            memcpy(tempString, stringData, size * sizeof(char));

            t->strPointer = tempString;
            t->args = args;
            break;
        }
        case 34: { // ASCII for "
            t->tokenValue = STR_ARR;

            int args = 0;
            
            int size = getStr(STR_MAX_LEN, 34, &args);

            char tempString[size];

            memcpy(tempString, stringData, size * sizeof(char));

            t->strPointer = tempString;
            t->args = args;
            break;
        }
        default:
            // determine if its an integer value
            if (isdigit(c)) {
                t->intValue = getint(c);
                t->tokenValue = INT_VALUE;
                break;
            
            // determine if its an identifier
            } else if (isalpha(c) || c == '_') { // identifiers cannot start with numbers
                int tokenType = 0; // stores the tokentype provided by detKeyword

                // scans for Identifier 
                int identLen = scanIdentifier(c);

                // determines if identifier is a keyword
                if ((tokenType = detKeyword())) {
                    t->tokenValue = tokenType;
                    break;
                }

                // do nothing else for now, we will add non identifier conditions later on            
                printf("Unrecognised identifier %s on line %d\n", identText, Line);
                exit(1);
            }

            printf("Unrecognised character %c on line %d\n", c, Line);
            exit(1);
        }
    return 1;
}
