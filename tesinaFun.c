#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <regex.h>
#include "tesina.h"
#include "parameters.h"

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
            } else {
                printf("\033[0;m");
                printf(" = %4.4g\n\n", risultato.risD);
                printf("\033[0m");
            }
        }  
    }
}

void stampaPaziente(struct pazienteDet risP) {
    printf("\033[1;37m");
    printf("\n----------");
    printf("| DATI PAZIENTE |");
    printf("----------\n");
    printf("|Cod. Fiscale: %s\n", risP.cf);
    printf("|Data Tamp: %s\n", risP.dataTamp);
    printf("|Esito Tamp: %s\n", risP.esitoTamp);
    printf("|Regione: %s\n", risP.regione);
    printf("|Ricoverato: %s\n", risP.isRicoverato == 1 ? "Sì" : "No");
    printf("-------------------------");
    printf("------------\n\n");
    printf("\033[0m");   
}

void stampaRegistro(struct registro risO) {
    
    Registro *iter;
    struct registro *reg = &risO;
    int counter = 1;

    printf("\033[1;37m");
    printf("\n----------");
    printf("| REGISTRO |");
    printf("----------\n");

    forEach(iter, reg)
    {
        printf("|%d.   %s\n",counter,iter->paziente.cf);
        counter+=1;
    }

    printf("--------------------");
    printf("------------\n\n");
    printf("\033[0m");
}






void treefree(struct ast *a)
{

    if (a == NULL) {
        return;
    }

    switch (a->nodetype)
    {

    case '+':
    case '-':
    case '*':
    case '/':
    case '|':
    case 'M':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
        treefree(a->l);
        treefree(a->r);
        break;
        
    case NODE_STRING:
        freeString((struct stringVal *) a);
        break;
    
    case NODE_DOUBLE:
        freeDouble((struct numVal *) a);
        break;
    
    case NODE_PAZIENTE:
        freePaziente((struct paziente *)a);
        break;

    case NODE_REGISTRO:
        freeRegistro(a);
        break;
    
    case NODE_EQUAL:
        freeAsgn((struct asgn *)a);
        break;
    
    case NODE_PRINT: 
        freePrint((struct print *)a);
        break;

    case NODE_GET:
        freeGet((struct get *)a);
        break;
    
    case NODE_ADD_PAZIENTE:
        freeAddPaziente((struct addPaziente *) a);
        break;

    case NODE_REFERENCE:
        freeRef((struct ref*) a);
        break;
    
    case NODE_GETPAZ:
        freeGetPaziente((struct getPaziente *) a);
        break;

    case NODE_PAZIENTE_FILTER:
        freePazienteFilter((struct numPositiviByFilter *) a);
        break;

    case NODE_NUMPAZ:
        freeNumPaz((struct numPazienti *)a );
        break;

    case NODE_NUMPOS:
        freeNumPos((struct numPositivi *)a );
        break;

    case NODE_NUMRIC:
        freeNumRic((struct numRicoverati *)a );
        break;

    default:
        printf("Errore interno di liberazione memoria\n");
    }
}

void freeNumPos(struct numPositivi *a) {
    
    if(a == NULL) {
        return;
    }

    free(a);

}

void freeNumRic(struct numRicoverati *a) {
    
    if(a == NULL) {
        return;
    }

    free(a);

}

void freeNumPaz(struct numPazienti *a) {
    
    if(a == NULL) {
        return;
    }

    free(a);

}

void freePazienteFilter(struct numPositiviByFilter *a) {
    
    if(a == NULL) {
        return;
    } 

    treefree(a->filter);
    free(a);
}


void freeGetPaziente(struct getPaziente *a) {
    
    if(a == NULL) {
        return;
    }

    treefree(a->key);
    free(a);
  
}

void freeRef(struct ref *a) {
    
    if(a == NULL) {
        return;
    }

    free(a);

}

void freeDouble(struct numval *a) {
    
    if(a == NULL) {
        return;
    }

    free(a);
}

void freeString(struct stringVal *a) {
    
    if(a == NULL) {
        return;
    }

    free(a);
}

void freePaziente(struct paziente *a) {
    
    if(a == NULL) {
        return;
    }

    treefree(a->cf);
    treefree(a->dataTamp);
    treefree(a->esitoTamp);
    treefree(a->isRicoverato);
    treefree(a->regione);
    free(a);
}

void freeRegistro(struct ast *a) {
    
    if(a == NULL) {
        return;
    }

    free(a);
}

void freeAsgn(struct asgn *a) {
    
    if(a == NULL) {
        return;
    } 

    treefree(a->v);
    free(a);
}

void freePrint(struct print *a) {
    
    if(a == NULL) {
        return;
    }  

    treefree(a->val);
    free(a);   
}

void freeGet(struct get *a) {

    if(a == NULL) {
        return;
    }  

    free(a);  
}

void freeAddPaziente(struct addPaziente *a) {
    
    if(a == NULL) {
        return;
    }

    treefree(a->paziente);
    free(a);  
}























/* Funzione per generare un ID casuale per il registro */
int createUID() {
    
    srand(time(0));

    int uid = (int)(rand() + 1);
    return uid;
}

void printNotValidCommand(char *s){
    printf("\033[0;31m");
    if(s){
        printf("%s.\n", s);
    }else{
        printf("Errore di sintassi, verificare le istruzioni inserite.\n");
    }
    printf("\033[0m");
}

void yyerror(char *s, ...)
{
    //va_list ap;
    //va_start(ap, s);
    //fprintf(stderr, "\033[0;31m");
    //fprintf(stderr, "%d: error: ", yylineno);
    //vfprintf(stderr, s, ap);
    //fprintf(stderr, "\n");
    //fprintf(stderr,"\033[0m");
    printNotValidCommand(s);
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
    int left;

    if (risLeft.risP.cf == NULL && risLeft.risD == NaN && risLeft.risO.idReg == 0){
       left = 2; // è una stringa
    }
    
    if (risLeft.risS == NULL && risLeft.risD == NaN && risLeft.risO.idReg == 0){
       left = 3; // è un paziente
    }
    
    if (risLeft.risO.idReg != 0){
       left = 4; // è un registro
    }
    
    if(risLeft.risD != NaN){
       left = 1; // è un double
    }

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