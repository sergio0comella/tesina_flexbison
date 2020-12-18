%option noyywrap nodefault yylineno
%{
    #include "headers/tesina.h"
    #include "tesina.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%

"STAMPA" { return STAMPA; }                 /* Stampa testo */

"DEF" { return MACRO; }                     /* Macro operazioni */

"IF"    { return IF; }
"ELSE"  { return ELSE; }   
"WHILE" { return WHILE; }                   /* Strutture condizionali e cicli */

"PAZIENTE"        { return PAZIENTE; }  
"getCF"           { return CF; }
"getDataTamp"     { return DATATAMP; }
"getEsitoTamp"    { return ESITOTAMP; }
"getReg"          { return REGIONE; }
"isRic"           { return ISRIC; }         /* Paziente e rispettivi "metodi" */

"REGISTRO" { return REGISTRO; } 
"ADD"      { return ADD; }
"GET"      { return GET; }
"NUMPAZ"   { return NPAZ; }
"NUMPOS"   { return NPOS; }
"NUMRIC"   { return NRIC; }
"POSIN"    { return POSIN; }
"IMPORT"   { return IMPORT; }
"EXPORT"   { return EXPORT; }               /* Registro e rispettivi "metodi" */

">"     { yylval.cmp = 1; return CMP; }
"<"     { yylval.cmp = 2; return CMP; }
"!="    { yylval.cmp = 3; return CMP; }
"=="    { yylval.cmp = 4; return CMP; }
">="    { yylval.cmp = 5; return CMP; }
"<="    { yylval.cmp = 6; return CMP; }    
"&&"    { yylval.cmp = 7; return CMP; }
"||"    { yylval.cmp = 8; return CMP; }     /* Operatori di comparazione */            

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
"." |
"{" |
"}" |
")" { return yytext[0]; }                   /* Operatori aritmetici */

"\""[a-zA-Z0-9" "\-"_"""/""."]+"\"" {yylval.string = malloc(sizeof(char)*strlen(yytext) + 1); 
                        strcpy(yylval.string,yytext); return STRING; }  /* String */


[0-9]+"."[0-9]*{EXP}? | 
[0-9]+{EXP}?            { yylval.d = atof(yytext); return NUMBER; }     /* Double e Int */



[a-zA-Z][a-zA-Z0-9]* { struct var* variabile = lookup(yytext); yylval.vr = variabile; return VAR; }    /* Variabili/nomi */


[ \t] { }
"//".* { }                                                            /* Commenti */

\n { return EOL; }

. { }

%%




