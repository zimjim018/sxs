%{
	int sl=0,ml=0;
%}

%%
"/*"[a-zA-Z0-9' '\n\t]+"*/" {ml++;}
"//".*  {sl++;}
%%

int main()
{
	yyin= fopen("1.c", "r");
	yyout = fopen("2.c", "w");
	yylex();
    	printf("Multiline comment count = %d,singleline comment count = %d\n",ml,sl );
	return 0;
}
