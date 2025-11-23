%{
#include <stdio.h>
int capitalCount = 0;
%}

%%

[A-Z]      { capitalCount++; }  // Count capital letters only
.|\n       { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a string: ");
    yylex();
    printf("Total number of capital letters: %d\n", capitalCount);
    return 0;
}
