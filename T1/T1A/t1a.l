%{
    int identifier;
    int operator;
    int bracket;
%}
%%
[+] {printf("+");operator++;}
[-] {printf("-");operator++;}
[*] {printf("*");operator++;}
[/] {printf("/");operator++;}
[a-zA-Z0-9]+ {identifier++;}
[(] {bracket++;}
[)] {bracket--;}
%%
main(){
    printf("ENTER THE EXPRESSION : ");
    yylex();
    printf("\nNUMBER OF OPERATORS : %d", operator);
    printf("\nNUMBER OF IDENTIFIERS : %d", identifier);
    if(operator >= identifier || bracket != 0){
        printf("INVALID EXPRESSION.");
    }else{
        printf("VALID EXPRESSION.");
    }
}