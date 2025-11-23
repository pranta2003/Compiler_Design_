%{
#include <stdio.h>
#include <string.h>
int compound = 0;
%}
%%
.*;.*\n                                { compound = 1; printf("Compound: %s\n", yytext); }
.*,([ \t])*((for|and|nor|but|or|yet|so))\b.*\n  { compound = 1; printf("Compound: %s\n", yytext); }
^.*\n                                   {
                                          if(!compound) printf("Simple: %s\n", yytext);
                                          compound = 0;
                                        }
.|\n                                    { /* consume */ }
%%

int yywrap() { return 1; }
int main(){
    yylex();
    return 0;
}
