%{
#include <stdio.h>
#include <string.h>
int id_count = 0;
const char* keywords[] = {
    "auto","break","case","char","const","continue","default","do","double","else","enum",
    "extern","float","for","goto","if","inline","int","long","register","restrict","return",
    "short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
    "volatile","while","_Bool","_Complex","_Imaginary", NULL
};
int is_keyword(const char* s){
    for(int i=0; keywords[i]!=NULL; ++i) if(strcmp(s,keywords[i])==0) return 1;
    return 0;
}
%}
%%
[A-Za-z_][A-Za-z0-9_]*   { if(!is_keyword(yytext)) { id_count++; } }
.|\n                     { /* ignore others */ }
%%

int yywrap() { return 1; }
int main(void){
    yylex();
    printf("\n\nIdentifiers: %d\n", id_count);
    return 0;
}
