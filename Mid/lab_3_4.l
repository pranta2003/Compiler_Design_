%{
#include <stdio.h>
%}

%%
"+"         { printf("Arithmetic Operator: %s\n", yytext); }
"-"         { printf("Arithmetic Operator: %s\n", yytext); }
"*"         { printf("Arithmetic Operator: %s\n", yytext); }
"/"         { printf("Arithmetic Operator: %s\n", yytext); }
"%"         { printf("Arithmetic Operator: %s\n", yytext); }

"=="        { printf("Relational Operator: %s\n", yytext); }
"!="        { printf("Relational Operator: %s\n", yytext); }
">"         { printf("Relational Operator: %s\n", yytext); }
"<"         { printf("Relational Operator: %s\n", yytext); }
">="        { printf("Relational Operator: %s\n", yytext); }
"<="        { printf("Relational Operator: %s\n", yytext); }

"&&"        { printf("Logical Operator: %s\n", yytext); }
"||"        { printf("Logical Operator: %s\n", yytext); }
"!"         { printf("Logical Operator: %s\n", yytext); }

[ \t\n]     ;   // Ignore whitespace
.           { printf("Invalid token: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter input: ");
    yylex();
    return 0;
}
