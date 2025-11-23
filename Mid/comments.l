%{
#include <stdio.h>
%}
%%
"//".*               { printf("COMMENT (SINGLE LINE): %s\n", yytext); }

"/*"([^*]|\*+[^*/])*\*+"/"    { printf("COMMENT (MULTI LINE): %s\n", yytext); }

.                        { printf("Invalid Input: %s\n", yytext); }

%%
int yywrap() {
    return 1;
}
int main() {
    printf("Input:\n");
    yylex();
    return 0;
}
