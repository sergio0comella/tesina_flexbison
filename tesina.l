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
")" { return yytext[0]; }

[0-9]+"."[0-9]*{EXP}? |
[0-9]+{EXP}?            { yylval.d = atof(yytext); return NUMBER; } /* Numeri */

[ \t] { }
"//".* { }

\n { return EOL; }

. { }

%%




