#ifndef ACG_H
#define ACG_H

int acg_add (int leftReg, int rightReg);
int acg_minus (int leftReg, int rightReg);
int acg_times (int leftReg, int rightReg);
int acg_div (int leftReg, int rightReg);
int acg_load (int intValue);

void acg_preamble ();

void acg_printInt(int reg);
void acg_postamble();

#endif
