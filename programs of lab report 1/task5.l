%{
#include <stdio.h>
%}

%%
^bb.*bb$    { printf("Matched: %s\n", yytext); }
^.*\n       { /* not matched */ }
.           { /* consume */ }
%%

int yywrap() {
    return 1;
}
int main(void){
    yylex();
    return 0;
}
