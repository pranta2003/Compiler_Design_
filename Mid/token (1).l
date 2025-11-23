%{
#include <stdio.h>
#include <string.h>
%}

%%

"int"|"float"|"char"|"if"|"else"|"while"|"return"  { printf("KEYWORD: %s\n", yytext); }

[0-9]+(\.[0-9]+)?     { printf("NUMBER: %s\n", yytext); }

"=="|"<="|">="|"!="   { printf("RELATIONAL OPERATOR: %s\n", yytext); }

"="|"+"|"-"|"*"|"/"   { printf("OPERATOR: %s\n", yytext); }

"("                  { printf("DELIMITER: %s\n", yytext); }
")"                  { printf("DELIMITER: %s\n", yytext); }
"{"                  { printf("DELIMITER: %s\n", yytext); }
"}"                  { printf("DELIMITER: %s\n", yytext); }
";"                  { printf("DELIMITER: %s\n", yytext); }
","                  { printf("DELIMITER: %s\n", yytext); }

\"[^\"]*\"           { printf("STRING: %s\n", yytext); }

"//".*               { printf("COMMENT (SINGLE LINE): %s\n", yytext); }

"/*"([^*]|\*+[^*/])*\*+"/"    { printf("COMMENT (MULTI LINE): %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("IDENTIFIER: %s\n", yytext); }

[ \t\n]+              ; // Ignore whitespace

.                     { printf("UNKNOWN: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter your code (Ctrl+D or Ctrl+Z to end):\n");
    yylex();
    return 0;
}
