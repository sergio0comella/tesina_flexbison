%{
#include <stdio.h>
#include <stdlib.h>
#include "headers/tesina.h"
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
%token ADD GET NPAZ NPOS NRIC POSIN
%token IMPORT EXPORT
%token STAMPA

%token <vr> USRVAR NUMVAR STRINGVAR PAZVAR REGVAR

%token EOL

/* Precedenza degli operatori */

%nonassoc ':'
%right '='
%nonassoc <cmp> CMP
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp condExp stmt seqOp paz reg pazvar regvar regfun

%start prog
%%
/*------------------------------------------------------------------------------
 * 
 * rules
 * 
 *----------------------------------------------------------------------------*/
prog:
    | prog stmt EOL          {processTree('P',$2); treefree($2); printf(""); }
    | prog stmt ';' EOL      {processTree('N',$2); treefree($2); printf(""); }
    | prog condExp EOL       {processTree('N',$2); treefree($2); printf(""); }
    | prog EOL               { printf(""); }
    | prog error EOL         { yyerrok; yyclearin;}
;


condExp: IF stmt ':' seqOp             { $$ = newCond('I',$2,$4,NULL); }
    | IF stmt ':' seqOp ELSE seqOp     { $$ = newCond('I',$2,$4,$6); }
    | WHILE stmt ':' seqOp             { $$ = newCond('W',$2,$4,NULL); }
;

seqOp: stmt
    | stmt ';' seqOp { $$ = newast('L', $1, $3); }
;

stmt: exp
    | paz
    | reg
    | regfun
    | '(' exp ')'                                                 { $$ = $2; }
    | stmt CMP stmt                                               { $$ = newCmp($2, $1, $3); }
    | USRVAR '=' stmt                                             { $$ = newasgn($1, $3); }
    | STRINGVAR '=' stmt                                          { $$ = newasgn($1, $3); }
    | NUMVAR '=' stmt                                             { $$ = newasgn($1, $3); }
    | STAMPA ':' stmt                                             { $$ = newPrint($3); }
;

paz: 
    PAZIENTE'(' exp ',' exp ',' exp ',' exp ',' exp ')'           { $$ = newPaziente('P',$3,$5,$7,$9,$11); }
    | PAZVAR '=' paz                                              { $$ = newasgn($1, $3); }
    | PAZVAR                                                      { $$ = newref($1); }
;

pazvar:
    PAZVAR '.' CF                                                 { $$ = newGet($1,1); }
    | PAZVAR '.' ESITOTAMP                                        { $$ = newGet($1,2); }
    | PAZVAR '.' DATATAMP                                         { $$ = newGet($1,3); }
    | PAZVAR '.' REGIONE                                          { $$ = newGet($1,4); }
    | PAZVAR '.' ISRIC                                            { $$ = newGet($1,5); }
;

reg:
    REGISTRO '('')'                                               { $$ = newRegistro('O'); }
    | REGVAR '=' reg                                              { $$ = newasgn($1, $3); }
    | REGVAR                                                      { $$ = newref($1); }
;

regfun:
    REGVAR '.' ADD '(' paz ')'                                    { $$ = addPaziente($1,$5); }
    | REGVAR '.' GET '(' exp ')'                                  { $$ = getPaziente($1,$5); }
    | REGVAR '.' IMPORT '(' exp ')'                               { $$ = import($1,$5); }
    | REGVAR '.' EXPORT '('')'                                    { $$ = export($1); }
;

regvar:
    REGVAR '.' NPAZ                                               { $$ = numPazienti($1); }
    | REGVAR '.' NPOS                                             { $$ = numPositivi($1); }
    | REGVAR '.' NRIC                                             { $$ = numRicoverati($1); }
    | REGVAR '.' POSIN '(' exp ')'                                { $$ = numPositiviByFilter($1,$5); }
;

exp:  pazvar
    | regvar
    | NUMBER                                                      { $$ = newnum($1); }
    | exp '+' exp                                                 { $$ = newast('+', $1,$3); }
    | exp '-' exp                                                 { $$ = newast('-', $1,$3); }
    | exp '*' exp                                                 { $$ = newast('*', $1,$3); }
    | exp '/' exp                                                 { $$ = newast('/', $1,$3); }
    | '|' exp                                                     { $$ = newast('|', $2, NULL); }
    | '-' exp %prec UMINUS                                        { $$ = newast('M', $2, NULL); }
    | USRVAR                                                      { $$ = newref($1); }
    | STRING                                                      { $$ = newString($1); }
    | DATE                                                        { $$ = newString($1); }
    | STRINGVAR                                                   { $$ = newref($1); }
    | NUMVAR                                                      { $$ = newref($1); }
;

%%
