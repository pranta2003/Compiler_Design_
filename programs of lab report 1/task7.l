%{
#include <stdio.h>
#include <string.h>
FILE *yyin;
long chars=0, words=0, spaces=0, lines=0;
%}

%%
[^\n ]+      { chars += yyleng; words++; }
[ ]+         { chars += yyleng; spaces += yyleng; }
\n           { chars++; lines++; }
%%

int yywrap() {
    return 1;
}
int main(){
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("Failed to open input.txt");
        return 1;
    }

    yylex();
    printf("Characters:%ld\nWords:%ld\nSpaces:%ld\nLines:%ld\n", chars,words,spaces,lines);

    fclose(yyin);
    return 0;
}


