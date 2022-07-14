%{
#include<stdio.h>
#include "y.tab.h"
extern int yylval;
%}

%%

[+|-|*|/|<|>|=]	{printf ("operator is %s\n",yytext); return OP;}

[0-9]+          {yylval=atoi(yytext);printf ("Number is %d\n",yylval);return DIG;}

void|for|if|int {printf ("keyword is %s\n",yytext);return KEY;}

[a-zA-Z0-9]+    {printf("identifier is %s\n",yytext);return ID;}
.	;
%%