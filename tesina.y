%{
#include <stdio.h>
#include <stdlib.h>
#include "tesina.h"
%}

/* Dichiarazione union per i tipi */
%union {
    struct ast *a;
    double d;
    char *string;
    struct var *vr;
}

/* Dichiarazione dei token */
%token <d> NUMBER
%token <string> STRING DATE

%token EOL

%token <vr> USRVAR

/* Precedenza degli operatori */
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp list 

%start calcseq
%%

calcseq:
    | calcseq list EOL { printf(" = %4.4g\n", eval($2)); treefree($2); printf(""); }
    | calcseq EOL     { printf(""); }   
;

list: exp 
    | exp ';' list { $$ = newast('L', $1, $3); }
;

exp: NUMBER                     { $$ = newnum($1); }
    | exp '+' exp               { $$ = newast('+', $1,$3); }
    | exp '-' exp               { $$ = newast('-', $1,$3); }
    | exp '*' exp               { $$ = newast('*', $1,$3); }
    | exp '/' exp               { $$ = newast('/', $1,$3); }
    | '|' exp                   { $$ = newast('|', $2, NULL); }
    | '(' exp ')'               { $$ = $2; }
    | '-' exp %prec UMINUS      { $$ = newast('M', $2, NULL); }
    | STRING                    { $$ = newString($1); }
    | DATE                      { $$ = newString($1); }
    | USRVAR                    { $$ = newref($1); }
    | USRVAR '=' exp            { $$ = newasgn($1, $3); }
;

%%

