#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <regex.h>
#include "headers/tesina.h"
#include "headers/parameters.h"

#define forEach(item, list) \
    for (item = list; item != NULL; item = item->pazienteSucc)

/* Funzione di hash che data una stringa ne restiusce il corrispetivo intero */
static unsigned hashFun(char *stringa)
{
    unsigned int hash = 0;
    unsigned c;

    while (c = *stringa++)
    {
        hash = hash * 9 ^ c; //Scorre tutti i caratteri della stringa e ne fa xor con hash * 9
    }

    return hash;
}

/* Funzione che dato un nome fornito dall'utente, restituisce la variabile corrispondente altrimenti ne istanzia una nuova */
struct var *lookup(char *nome)
{

    struct var *variabile = &vartab[hashFun(nome) % NHASH]; //Prendo la variabile della tabella nella posizione data dall'hash del nome

    int counter = NHASH; //Contatore della dimensione della tabella

    /* Scorro la tabella, se trovo una variabile con stesso nome la restituisco altrimenti la istanzio */
    while (--counter)
    {

        //Ho trovato la variabile, la restituisco
        if (variabile->nome && !strcmp(variabile->nome, nome))
        {
            return variabile;
        }

        //Ho trovato "una cella" della tabella vuota, quindi istanzio la variabile
        if (!variabile->nome)
        {

            variabile->varType = NULL;
            variabile->nome = strdup(nome);
            variabile->valore = 0;
            variabile->string = NULL;
            variabile->paziente.cf = NULL;
            variabile->paziente.dataTamp = NULL;
            variabile->paziente.esitoTamp = NULL;
            variabile->paziente.regione = NULL;
            variabile->paziente.isRicoverato = 0;
            variabile->registro.idReg = 0;
            variabile->registro.indice = 0;
            variabile->registro.occupato = 0;
            variabile->registro.pazienteSucc = NULL;
            variabile->macro = NULL;

            return variabile;
        }

        //Se esce dai limiti dell'array, ricomincia
        if (++variabile >= vartab + NHASH)
            variabile = vartab;
    }

    printNotValidCommand("Overflow tabella variabili\n");
    abort();
}


/* Funzione che stampa i risultati delle valutazioni */
void processTree(int print, struct ast *a)
{

    struct result risultato = eval(a);

    if (print == 'P' && risultato.flagPrint == 0)
    {
        if (sizeof(risultato.risS) > 0 && risultato.risS != NULL) {
            printf("\033[0;33m");
            printf(" = %s\n\n", risultato.risS);
            printf("\033[0m");
        } else if (risultato.risP.cf != NULL) {
            stampaPaziente(risultato.risP);
        } else {
            if(risultato.risO.idReg != NULL && risultato.risO.occupato == 0) {
                printf("\033[0;32m");
                printf("Registro inizializzato e vuoto.\n\n");
                printf("\033[0m");
            } else if(risultato.risO.idReg != NULL && risultato.risO.occupato == 1) {
                stampaRegistro(risultato.risO);
            } else if(risultato.risD != NaN){
                printf("\033[0;m");
                printf(" = %2.2f\n\n", risultato.risD);
                printf("\033[0m");
            }
        }  
    }
}

void printNotValidCommand(char *s){
    printf("\033[0;31m");
    printf("%s\n", s);
    printf("\033[0m");
}

void yyerror(char *s, ...)
{
    printNotValidCommand("Errore di sintassi: Comando non riconosciuto.");
}

int match(const char *string, const char *pattern)
{
    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return 0;
    int status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
    if (status != 0)
        return 0;
    return 1;
}

int findType(struct result risLeft) {
    int left = 0;

    if (risLeft.risP.cf == NULL && risLeft.risD == NaN && risLeft.risO.idReg == 0){
       left = 2; // è una stringa
    }
    
    //printf("left1: %d\n", left);

    if (risLeft.risS == NULL && risLeft.risD == NaN && risLeft.risO.idReg == 0){
       left = 3; // è un paziente
    }
    
    if (risLeft.risO.idReg != 0){
       left = 4; // è un registro
    }
    
    if(risLeft.risD != NaN){
       left = 1; // è un double
    }

    //printf("left2: %d\n", left);

   return left;
}

int main(int argc, char const *argv[])
{
    printf("");
    if(!yyparse()){
        yylex_destroy();
        return yyparse();
    }else{
        return yyparse();
    }
}