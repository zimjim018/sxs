%{
#include<stdio.h>
%}
%token NUM
%left '+' '-'
%left '*' '/'
%%
expr: e{printf("Result=%d",$1); return 0;};
e: e'+'e {$$=$1+$3;}|
e'-'e {$$=$1-$3;}|
e'*'e {$$=$1*$3;}|
e'/'e {$$=$1/$3;}|
'('e')'{$$=$2;}|
NUM {$$=$1;}
%%
main()
{
	printf("enter the expression\n");
	yyparse();
	printf("Valid expression\n");
}
yyerror()
{
	printf("Invalid expression");
	exit(0);
}