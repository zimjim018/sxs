%{
#include <stdio.h>
#include <stdlib.h>
%}
%token A B
%%
str: s '\n' { return 0;}
s: x B;
x: A T ;
T: T A
| ;
%%
int main()
{
    printf("type the string\n");
    yyparse();
    printf("valid string\n");
}

yyerror()
{
    printf("invalid string\n");
    exit(0);
}