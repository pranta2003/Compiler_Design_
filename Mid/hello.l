%{
#include<stdio.h>
%}

%%

[aeiouAEIOU] {printf("%s is a voule.", yytext);}
[a-zA-Z] {printf("%s is a consonent.", yytext);}
.|\n {printf("%s is a spatiol charecter.");}

	
%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}