#include "Header_Files\defs.h"
#include "Header_Files\data.h"
#include "Header_Files\lexer.h"

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

int scanFile(struct token *t) {
    int c;

    c = skipwhitespace(); // get the next character that is not a whitespace

    switch (c) {
        case EOF:
            t->tokenValue = T_EOF;
            break;
        case '+':
            t->tokenValue = T_PLUS;
            break;
        case '-':
            t->tokenValue = T_MINUS;
            break;
        case '*':
            t->tokenValue = T_TIMES;
            break;
        case '/':
            t->tokenValue = T_DIV;
            break;
        default:
            if (isdigit(c)) {
                t->intValue = getint(c);
                t->tokenValue = T_INTLIT;
                break;
            }

            printf("Unrecognised character %c on line %d\n", c, Line);
            exit(1);
        }
    return 1;
}