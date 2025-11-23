%{
#include <stdio.h>
%}

%%
^.*aa$      { printf("Matched: %s\n", yytext); }
^.*\n       { /* not matched; consume line */ }
.           { /* consume */ }
%%

int yywrap() {
    return 1;
}
int main(){
    yylex();
    return 0;
}
