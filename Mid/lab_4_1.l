%option noyywrap
%{
    #include <stdio.h>
    #include <string.h>
    FILE *yyin;

    int identtifier = 0;
    int str = 0;
    int key = 0;
    
%}



%%

"int"|"float"|"char"|"if"|"else"|"while"|"return"|"printf"  { key++; }
\"[^\"]*\"           { str++; }
[a-zA-Z_][a-zA-Z0-9_]*  { identtifier++; }
[ \t\n]+              ; // Ignore whitespace
.|\n ;
%%

int main(int argc, char **argv) {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("Failed to open input.txt");
        return 1;
    }

    yylex();
    printf("Identifire: %d\n", identtifier);
    printf("String: %d\n", str);
    printf("Keyword: %d\n", key);

    fclose(yyin);
    return 0;
}
