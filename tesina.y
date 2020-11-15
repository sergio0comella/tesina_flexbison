%{
#include <stdio.h>
#include <stdlib.h>
#include "tesina.h"
#define YYERROR_VERBOSE 1
  //per eliminare i warning
    int yylex(void);
%}

/* Dichiarazione union per i tipi */
%union {
    struct ast *a;
    double d;
    char *string;
    struct var *vr;
    int cmp;
}

/* Dichiarazione dei token */
%token <d> NUMBER
%token <string> STRING DATE

%token IF THEN ELSE WHILE 
%token PAZIENTE 
%token CF ESITOTAMP DATATAMP REGIONE ISRIC
%token REGISTRO

%token <vr> USRVAR

%token EOL

/* Precedenza degli operatori */

%right '='
%nonassoc <cmp> CMP
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp condExp stmt seqOp

%start prog
%%
/*------------------------------------------------------------------------------
 * 
 * rules
 * 
 *----------------------------------------------------------------------------*/
prog:
    | prog stmt EOL          {processTree('P',$2); /*treefree($2);*/ printf(""); }
    | prog stmt ';' EOL      {processTree('N',$2); /*treefree($2);*/ printf(""); }
    | prog condExp EOL       {processTree('N',$2); /*treefree($2);*/ printf(""); }
    | prog EOL               { printf(""); }
    | prog error EOL         { yyerrok; yyclearin;}
    ;
;

condExp: IF stmt ':' seqOp             { $$ = newCond('I',$2,$4,NULL); }
    | IF stmt ':' seqOp ELSE seqOp     { $$ = newCond('I',$2,$4,$6); }
    | WHILE stmt ':' seqOp             { $$ = newCond('W',$2,$4,NULL); }
;

seqOp: stmt
    | stmt ';' seqOp { $$ = newast('L', $1, $3); }
;

stmt: exp
    | stmt CMP stmt                                               { $$ = newCmp($2, $1, $3); }
    | USRVAR '=' stmt                                             { $$ = newasgn($1, $3); }
    | PAZIENTE'(' exp ',' exp ',' exp ',' exp ',' exp ')'         { $$ = newPaziente('P',$3,$5,$7,$9,$11); }
    | USRVAR '.' CF                                               { $$ = newGet($1,1); }
    | USRVAR '.' ESITOTAMP                                        { $$ = newGet($1,2); }
    | USRVAR '.' DATATAMP                                         { $$ = newGet($1,3); }
    | USRVAR '.' REGIONE                                          { $$ = newGet($1,4); }
    | USRVAR '.' ISRIC                                            { $$ = newGet($1,5); }
    | REGISTRO'('')'                                              { $$ = newRegistro('O'); }
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
;

%%
