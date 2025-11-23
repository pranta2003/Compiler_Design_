%option noyywrap
%{
    #include <stdio.h>
    #include <string.h>
%}


%%

"a" { printf("Matched\n"); }
[a*b+]  { printf("Matched\n"); }
"abb"  { printf("Matched\n") ;}

[ \t\n]+              ; // Ignore whitespace
.|\n ;
%%

int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}
