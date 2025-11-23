%{
#include "expr_eval.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[+\-*/()]{1}    { return yytext[0]; }
[ \t\r]+        { /* ignore whitespace */ }
\n              { return 0; }
.               { return yytext[0]; }

%%

int yywrap() { return 1; }
