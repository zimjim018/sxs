%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	int op=0, dig=0, key=0, id=0;
%}

%token OP ID KEY DIG

%% 
input : DIG input	{dig++;}
	| ID input	{id++;}
	| OP input 	{op++;}
	| KEY input 	{key++;}
	|ID 		{id++}
	|OP		{op++;}
	|KEY		{key++;}
	| DIG		{dig++;}
	;
%%

void yyerror()
{
	printf("ERROR");
	exit(0);
}
FILE *yyin;
int main()
{
	FILE *fp;
	fp = fopen ("output.c", "r");
	yyin = fp;
	do{
		yyparse();
	} while (!feof(yyin));

    printf ("count of, \n Keyword = %d\nIdentifier = %d\nOperator = %d\nDigit = %d   \n",key,id,op,dig);
	fclose (fp);	
    return 0;
}