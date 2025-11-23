%{
#include <stdio.h>
#include <ctype.h>
int vowels = 0, consonants = 0;
%}
%%
[AEIOUaeiou]     { vowels++; }
[A-Za-z]         { consonants++; }
.|\n             { /* ignore other chars */ }
%%
int yywrap(){}
int main() {
    yylex();
    printf("Vowels: %d\nConsonants: %d\n", vowels, consonants);
    return 0;
}
