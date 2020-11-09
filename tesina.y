%{
#include <stdio.h>
#include <stdlib.h>
#include "tesina.h"
%}

/* Dichiarazione union per i tipi */
%union {
    struct ast* a;
    double d;
}

/* Dichiarazione dei token */
%token <d> NUMBER
%token EOL

/* Precedenza degli operatori */
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp 

%%

calcseq:
    | calcseq exp EOL { printf(" = %4.4g\n", eval($2)); treefree($2); printf("> "); }
    | calcseq EOL { printf(""); }   
;

exp: NUMBER { $$ = newnum($1); }
    | exp '+' exp { $$ = newast('+', $1,$3); }
    | exp '-' exp { $$ = newast('-', $1,$3); }
    | exp '*' exp { $$ = newast('*', $1,$3); }
    | exp '/' exp { $$ = newast('/', $1,$3); }
    | '|' exp { $$ = newast('|', $2, NULL); }
    | '(' exp ')' { $$ = $2; }
    | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
;

%%

