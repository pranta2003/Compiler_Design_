%{
#include <stdio.h>
%}

%%
^[0-9]{2}1[0-9]{3}9[0-9]*$   { printf("Valid: %s\n", yytext); }
^[0-9]+\n?                   { printf("Invalid: %s\n", yytext); }
^.*\n                        { /* ignore non-numeric lines */ }
%%

int yywrap() {
    return 1;
}
int main(){
    yylex();
    return 0;
}
