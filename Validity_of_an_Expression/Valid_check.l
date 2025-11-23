%{
#include "expr_valid.tab.h"
%}

%%
[0-9]+          { return NUMBER; }       /* integer */
[+\-*/()]       { return yytext[0]; }    /* operators and parentheses */
[ \t\r]+        { /* ignore whitespace */ }
\n              { return 0; }            /* end of input line */
.               { return yytext[0]; }    /* any other single char */
%%

int yywrap() { 
return 1;
 }
