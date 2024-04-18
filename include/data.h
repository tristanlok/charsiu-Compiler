// Keep this here for now
#include "defs.h"

extern int Line; // Current Line
extern int Putback; // If there is a character to put back
extern FILE *Infile; // File that stores the code to compiler
extern FILE *Outfile; // File that stores the assembly code generated
extern struct token Token; // Most recent token scanned (figure out why)
extern char identText[IDENT_MAX_LEN + 1]; // Char array to store Identifier (Length is max + 1 as the extra byte is for null terminator)
extern char stringData[STR_MAX_LEN + 1]; // Char array to store string


// .data .bss & .text section
extern int dataLen;
extern char *asmData;
extern int bssLen;
extern char *asmBss;
extern int textLen;
extern char *asmText;
