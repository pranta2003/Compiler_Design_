%{
#include <stdio.h>
#include <ctype.h>
int upperc = 0, lowerc = 0;
%}
%%
[A-Z]     { upperc++; }
[a-z]     { lowerc++; }
.|\n      { /* ignore */ }
%%
int yywrap(){}
int main() {
    yylex();
    printf("\n\nUppercase: %d\nLowercase: %d\n", upperc, lowerc);
    return 0;
}
