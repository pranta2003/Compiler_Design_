%option noyywrap
%{
#include<stdio.h>
#include "alif.tab.h"
%}

%%

[0-9]+    { yylval = atoi(yytext); return NUMBER; }
[ \t\n]+  ;  // skip whitespace
"+"       { return '+'; }
"-"       { return '-'; }
"*"       { return '*'; }
"/"       { return '/'; }
"%"       { return '%'; }
"="       { return '='; }
"("       { return '('; }
")"       { return ')'; }
[a-zA-Z]+ { return VARIABLE; }

.         { printf("Unknown character: %s\n", yytext); return 0; }

%%
