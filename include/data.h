// Keep this here for now
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int Line; // Current Line
extern int Putback; // If there is a character to put back
extern FILE *Infile; // 
extern struct token Token; // Most recent token scanned (figure out why)