// Keep this here for now
#include <stdio.h>
#include <stdlib.h> 

//Add these back if they are truly necassary
//#include <string.h>
//#include <ctype.h>

extern int Line; // Current Line
extern int Putback; // If there is a character to put back
extern FILE *Infile; // File that stores the code to compiler
extern FILE *Outfile; // File that stores the assembly code generated
extern struct token Token; // Most recent token scanned (figure out why)
