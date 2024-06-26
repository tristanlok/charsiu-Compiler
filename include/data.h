// Keep this here for now
#include "defs.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

extern int Line; // Current Line
extern int Putback; // If there is a character to put back
extern FILE *Infile; // File that stores the code to compiler
extern FILE *Outfile; // File that stores the assembly code generated
extern struct token Token; // Most recent token scanned (figure out why)
extern char identText[IDENT_MAX_LEN + 1]; // Char array to store Identifier (Length is max + 1 as the extra byte is for null terminator)
