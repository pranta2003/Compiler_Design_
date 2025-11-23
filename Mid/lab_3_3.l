%{
#include<stdio.h>
%}
%%
[/]{1}[/]{1}[ a-z A-Z 0-9 ^(a-zA-Z0-9)]* printf("Single Line Comment");
[/]{1}[*]{1}[ a-z A-Z 0-9 ^a-z^A-Z^0-9]*[*]{1}[/]{1} printf("MultiLine Comment");
.*                          { printf("This is NOT a comment.\n"); }
%%
int yywrap() {
    return 1;
}

int main() {
    printf("Enter a line:\n");
    yylex();
    return 0;
}
