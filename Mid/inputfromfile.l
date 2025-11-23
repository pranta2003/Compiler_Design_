%option noyywrap
%{
    #include <stdio.h>
    FILE *yyin;
%}

%%

(.|\n)+    { printf("%s", yytext); }

%%

int main(int argc, char **argv) {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("Failed to open input.txt");
        return 1;
    }

    yylex();

    fclose(yyin);
    return 0;
}
