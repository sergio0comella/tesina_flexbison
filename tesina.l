%option noyywrap nodefault yylineno
%{
    #include "tesina.h"
    #include "tesina.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%

"IF"    { return IF; }
"ELSE"  { return ELSE; }   
"WHILE" { return WHILE; }  /* Strutture condizionali e cicli */

"PAZIENTE"        { return PAZIENTE; }  
"getCF"           { return CF; }
"getDataTamp"     { return DATATAMP; }
"getEsitoTamp"    { return ESITOTAMP; }
"getRegione"      { return REGIONE; }
"getIsRicoverato" { return ISRIC; }     /* Paziente e rispettivi "metodi" */

">"     { yylval.cmp = 1; return CMP; }
"<"     { yylval.cmp = 2; return CMP; }
"!="    { yylval.cmp = 3; return CMP; }
"=="    { yylval.cmp = 4; return CMP; }
">="    { yylval.cmp = 5; return CMP; }
"<="    { yylval.cmp = 6; return CMP; }  /* Operatori di comparazione */

"+" |
"-" |
"/" |
"*" |
"(" |
"|" |
"=" |
";" |
":" |
"," |
")" { return yytext[0]; }  /* Operatori aritmetici */

"\""[a-zA-Z0-9\-]+"\"" {yylval.string = malloc(sizeof(char)*strlen(yytext) + 1); 
                        strcpy(yylval.string,yytext); return STRING; }  /* String */

([0-2][0-9]|(3)[0-1])(\/)(((0)[0-9])|((1)[0-2]))(\/)\d{4} {yylval.string = malloc(sizeof(char)*strlen(yytext) + 1); 
                                                           strcpy(yylval.string,yytext); return DATE; }  /* Date */


[0-9]+"."[0-9]*{EXP}? | 
[0-9]+{EXP}?            { yylval.d = atof(yytext); return NUMBER; } /* Double e Int */

[a-zA-Z][a-zA-Z0-9]* { yylval.vr = lookup(yytext); return USRVAR; }

[ \t] { }
"//".* { }

\n { return EOL; }

. { }

%%




