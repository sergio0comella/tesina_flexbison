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
%token MACRO
%token AND OR

%token <vr> VAR

%token EOL

/* Precedenza degli operatori */

%nonassoc ':'
%right '='
%nonassoc <cmp> CMP
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp condExp stmt seqOp paz reg pazvar regvar regfun macroOp macroEval stmtBlock

%start prog
%%
/*------------------------------------------------------------------------------
 * 
 * rules
 * 
 *----------------------------------------------------------------------------*/
prog:
    | prog stmt EOL          { processTree('P',$2); treefree($2); }
    | prog stmt ';' EOL      { processTree('N',$2); treefree($2); }
    | prog macroEval EOL     { processTree('N',$2); }
    | prog condExp EOL       { processTree('N',$2); }
    | prog macroOp EOL       { processTree('N',$2); }
    | prog EOL               { printf(""); }
    | prog error EOL         { yyerrok; yyclearin;}
;

macroEval:
    VAR '('')'                    { $$ = newMacroCall($1); }
;

macroOp:
    MACRO VAR '{' EOL stmtBlock '}' { $$ = newMacro($2,$5); }
;

stmtBlock: stmt EOL
    | condExp EOL
    | stmtBlock stmt EOL           { $$ = newast('L', $1, $2); }
    | stmtBlock condExp EOL        { $$ = newast('L', $1,$2); }
;

condExp: 
    IF stmt ':' seqOp                  { $$ = newCond('I',$2,$4,NULL); }
    | IF stmt ':' seqOp ELSE seqOp     { $$ = newCond('I',$2,$4,$6); }
    | WHILE stmt ':' seqOp             { $$ = newCond('W',$2,$4,NULL); }
;

seqOp: stmt
    | stmt ';' seqOp                   { $$ = newast('L', $1, $3); }
;

stmt: exp
    | paz
    | reg
    | regfun
    | stmt CMP stmt                                               { $$ = newCmp($2, $1, $3); }
    | VAR '=' stmt                                                { $$ = newasgn($1, $3); }
    | STAMPA ':' stmt                                             { $$ = newPrint($3); }
;

paz: 
    PAZIENTE'(' exp ',' exp ',' exp ',' exp ',' exp ')'           { $$ = newPaziente('P',$3,$5,$7,$9,$11); }
;

pazvar:
    VAR '.' CF                                                 { $$ = newGet($1,1); }
    | VAR '.' ESITOTAMP                                        { $$ = newGet($1,2); }
    | VAR '.' DATATAMP                                         { $$ = newGet($1,3); }
    | VAR '.' REGIONE                                          { $$ = newGet($1,4); }
    | VAR '.' ISRIC                                            { $$ = newGet($1,5); }
;

reg:
    REGISTRO '('')'                                               { $$ = newRegistro('O'); }
;

regfun:
    VAR '.' ADD '(' stmt ')'                                    { $$ = addPaziente($1,$5); }
    | VAR '.' GET '(' exp ')'                                   { $$ = getPaziente($1,$5); }
    | VAR '.' IMPORT '(' exp ')'                                { $$ = import($1,$5); }
    | VAR '.' EXPORT '('')'                                     { $$ = export($1); }
;

regvar:
    VAR '.' NPAZ                                               { $$ = numPazienti($1); }
    | VAR '.' NPOS                                             { $$ = numPositivi($1); }
    | VAR '.' NRIC                                             { $$ = numRicoverati($1); }
    | VAR '.' POSIN '(' exp ')'                                { $$ = numPositiviByFilter($1,$5); }
;

exp:  pazvar
    | regvar
    | NUMBER                                                      { $$ = newnum($1); }
    | exp '+' exp                                                 { $$ = newast('+', $1,$3); }
    | exp '-' exp                                                 { $$ = newast('-', $1,$3); }
    | exp '*' exp                                                 { $$ = newast('*', $1,$3); }
    | exp '/' exp                                                 { $$ = newast('/', $1,$3); }
    | '|' exp                                                     { $$ = newast('|', $2, NULL); }
    | '-' exp %prec UMINUS                                        { $$ = newast('N', $2, NULL); }
    | VAR                                                         { $$ = newref($1); }
    | STRING                                                      { $$ = newString($1); }
    | '(' stmt ')'                                                { $$ = $2; }
;

%%
