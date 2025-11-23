%{
#include <stdio.h>
int charCount = 0;
%}

%%

.          { charCount++; }  // Count every character
\n         { return 0; }     // Stop on newline

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a string: ");
    yylex();
    printf("Total number of characters: %d\n", charCount);
    return 0;
}
