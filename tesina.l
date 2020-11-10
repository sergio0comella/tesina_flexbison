%option noyywrap nodefault yylineno
%{
    #include "tesina.h"
    #include "tesina.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"/" |
"*" |
"(" |
"|" |
"=" |
";" |
")" { return yytext[0]; }

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




