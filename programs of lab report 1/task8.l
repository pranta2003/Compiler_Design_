%{
#include <stdio.h>
int c = 0, m = 0;
%}

%%
[/]{1}[/]{1}[a-z A-Z0-9]*          { c++; }
[/]{1}[*]{1}[a-z A-Z0-9]*[*]{1}[/]{1}   { m++; }
.*|\n*                          { ; }
%%

int yywrap() { return 1; }
int main() {
    printf("Enter code (Ctrl+D to stop):\n");
    yylex();
    printf("\n\nComment Lines : %d", c+m);
    return 0;
}