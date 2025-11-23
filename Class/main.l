%{
    #include<stdio.h>
    // FILE *yyin;
%}

%%
^.*aa$          {printf("Maatched: %s\n", yytext);}
^.*[^.*aa$]    {printf("Not Maatched: %s\n", yytext);}
.|\n                ;
%%

int yywrap() {
    return 1;
}
int main() {
    printf("Input: ");
    yylex();

    return 0;
}