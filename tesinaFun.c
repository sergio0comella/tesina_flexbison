#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include "tesina.h"

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

            return variabile;
        }

        //Se esce dai limiti dell'array, ricomincia
        if (++variabile >= vartab + NHASH)
            variabile = vartab;
    }

    yyerror("Overflow tabella variabili\n");
    abort();
}


/* Funzione che stampa i risultati delle valutazioni */
void processTree(int print, struct ast *a)
{

    struct result risultato = eval(a);

    if (print == 'P')
    {
        if (sizeof(risultato.risS) > 0 && risultato.risS != NULL) {
            printf("\033[0;33m");
            printf(" = %s\n\n", risultato.risS);
            printf("\033[0m");
        } else if (risultato.risP.cf != NULL) {
            printf("\033[1;37m");
            printf("\n----------");
            printf("| DATI PAZIENTE |");
            printf("----------\n");
            printf("|Cod. Fiscale: %s\n", risultato.risP.cf);
            printf("|Data Tamp: %s\n", risultato.risP.dataTamp);
            printf("|Esito Tamp: %s\n", risultato.risP.esitoTamp);
            printf("|Regione: %s\n", risultato.risP.regione);
            printf("|Ricoverato: %s\n", risultato.risP.isRicoverato == 1 ? "Sì" : "No");
            printf("-------------------------");
            printf("------------\n");
            printf("\033[0m");
        } else if(risultato.risO.idReg != NULL) {
            printf("\033[0;32m");
            printf("Registro creato correttamente.\n\n");
            printf("\033[0m");
        } else {
            printf("\033[0;m");
            printf(" = %4.4g\n\n", risultato.risD);
            printf("\033[0m");
        }
    }
}


void treefree(struct ast *a)
{

    switch (a->nodetype)
    {

    case '+':
    case '-':
    case '*':
    case '/':
    case 'L':
        treefree(a->r);

    case 'M':
    case '|':
        treefree(a->l);

    case 'D':
    case 'R':
        free(a);
        break;

    case '=':
        free(((struct asgn *)a)->v);
        break;

    default:
        printf("Errore interno di liberazione memoria");
    }
}

/* Funzione per generare l'ID del registro in maniera univoca e casuale */
int createUID() {
    
    srand(time(0));

    int uid = (int)(rand() + 1);
    return uid;
}

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "\033[0;31m");
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    fprintf(stderr,"\033[0m");
    //printNotValidCommand();
}

void printNotValidCommand(){
    printf("\033[0;31m");
    printf("Ultimo comando inserito non riconosciuto. Riprova.\n");
    printf("\033[0m");
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