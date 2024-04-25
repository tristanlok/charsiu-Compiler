#ifndef ACG_H
#define ACG_H

static void verifyCharAlloc (int currLen, int maxLen, char *src, char *dest);

int acg_add (int left, int right);
int acg_minus (int left, int right);
int acg_times (int left, int right);
int acg_div (int left, int right);
int acg_loadInt (int intValue);
int acg_loadStr (char *strValue);

void acg_print(int mainStack, int argIdx, int *argList);

void acg_preamble ();

void acg_printInt();
void acg_postamble();

#endif
