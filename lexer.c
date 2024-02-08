#include "token.h"
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

int scan(struct token *t) {
    int c;

    c = skipwhitespace();

    switch (c) {
        case EOF:
            return 0;
        case '+':
            t->token = PLUS;
            break;
        case '-':
            t->token = MINUS;
            break;
        case '*':
            t->token = TIMES;
            break;
        case '/':
            t->token = DIV;
            break;
        default:
            if (isdigit(c)) {
                t->intValue = getint(c);
                t->token = INTLIT;
                break;
            }

            printf("Unrecognised character %c on line %d\n", c, Line);
            exit(1);
        }
    return 1;
}