#ifndef HELPER_H
#define HELPER_H

int is_token(int tokenValue);
int next_token(int tokenValue); 
void syntax_err();
void missing_err(char *str);

#endif
