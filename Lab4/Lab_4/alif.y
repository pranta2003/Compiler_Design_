%{
    #include<stdio.h>
    #include<stdlib.h>

    int yylex(void);
    void yyerror(const char *s);
%}
%token NUMBER
%token VARIABLE

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%

S: E {
       printf("Result: %d\n", $1);
     }
 | VARIABLE '=' E {
       printf("Result: %d\n", $3);
     }
 ;

E: E '+' E {
        $$ = $1 + $3;
    }
 | E '-' E {
        $$ = $1 - $3;
    }
 | E '*' E {
        $$ = $1 * $3;
    }
 | E '/' E {
        if ($3 == 0) {
            yyerror("division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
 | E '%' E {
        if ($3 == 0) {
            yyerror("modulus by zero");
            $$ = 0;
        } else {
            $$ = $1 % $3;
        }
    }
 | '(' E ')' {
        $$ = $2;
    }
 | NUMBER {
        $$ = $1;
    }
 | VARIABLE {
        // For now, just return 0 for variables (or you can implement symbol table)
        $$ = 0;
    }
 ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "Error: %s\n", s);
}

int main()
{
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}