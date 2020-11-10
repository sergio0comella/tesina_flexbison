#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tesina.h"

/* Funzione di hash che data una stringa ne restiusce il corrispetivo intero */
static unsigned hashFun(char *stringa) {
    unsigned int hash = 0;
    unsigned c;

    while (c = *stringa++) {
        hash = hash*9 ^ c;            //Scorre tutti i caratteri della stringa e ne fa xor con hash * 9
    }

    return hash;
}

/* Funzione che dato un nome fornito dall'utente, restituisce la variabile corrispondente altrimenti ne istanzia una nuova */
struct var *lookup(char *nome) {

    struct var *variabile = &vartab[hashFun(nome)%NHASH]; //Prendo la variabile della tabella nella posizione data dall'hash del nome

    int counter = NHASH;                //Contatore della dimensione della tabella

    /* Scorro la tabella, se trovo una variabile con stesso nome la restituisco altrimenti la istanzio */
    while(--counter) {          

        //Ho trovato la variabile, la restituisco 
        if(variabile->nome && !strcmp(variabile->nome, nome)) {
            return variabile;
        }

        //Ho trovato "una cella" della tabella vuota, qunindi istanzio la variabile
        if(!variabile->nome) {

            variabile->nome = strdup(nome);
            variabile->valore = 0;

            return variabile;
        }

        //Se esce dai limiti dell'array, ricomincia
        if(++variabile >= vartab+NHASH)
            variabile = vartab;
    }

    yyerror("Overflow tabella variabili\n");
    abort();

}

struct ast *newast(int nodetype, struct ast *l, struct ast *r) {

    struct ast *a = malloc(sizeof(struct ast));

    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = nodetype;
    a->l = l;
    a->r = r;

    return a;

}

struct ast *newnum(double d) {

    struct numval *a = malloc(sizeof(struct numval));
    
    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'D';
    a->number = d;

    return (struct ast *)a;

}

struct ast *newString(char *string) {

    struct stringVal *a = malloc(sizeof(struct stringVal));
    
    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'S';
    a->string = string;

    return (struct ast *)a;

}

struct ast *newref(struct var* vr) {
    
    struct ref *a = malloc(sizeof(struct asgn));
    
    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'R';
    a->var = vr;

    return (struct ast *)a;

}

struct ast *newasgn(struct var *vr, struct ast *v) {
    
    struct asgn *a = malloc(sizeof(struct asgn));
    
    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = '=';
    a->var = vr;
    a->v = v;

    return (struct ast *)a;

}

double eval(struct ast *a) {

    double v;

    switch(a->nodetype) {
        /* Numeri (double) */
        case 'D': v = ((struct numval*)a)->number; break; 

        /* Stringa */
        case 'S': 

        /* Assegnamento */
        case '=': ((struct asgn *)a)->var->valore = eval(((struct asgn *)a)->v); break;

        /* Reference */
        case 'R': v = ((struct ref *)a)->var->valore; break;

        /* Operazioni classiche */
        case '+': v = eval(a->l) + eval(a->r); break;
        case '-': v = eval(a->l) - eval(a->r); break;
        case '*': v = eval(a->l) * eval(a->r); break;
        case '/': v = eval(a->l) / eval(a->r); break;
        case '|': v = eval(a->l); if(v < 0) v = -v; break;
        case 'M': v = -eval(a->l); break;

        /* Lista di istruzioni */
        case 'L': eval(a->l); v = eval(a->r); break;

        default: printf("Errore interno di valutazione");
    }

    return v;
}

void treefree(struct ast *a) {

    switch(a->nodetype) {

        case '+':
        case '-':
        case '*':
        case '/':
        case 'L':
            treefree(a->r);
   
        case 'M':
        case '|':
            treefree(a->l);

        case 'D': case'R': free(a); break;

        case '=': free( ((struct asgn *)a)->v); break;

        default: printf("Errore interno di liberazione memoria");
    }
}







void yyerror(char *s,...) {
    va_list ap; 
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno); 
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main(int argc, char const *argv[])
{
    printf("");
    return yyparse();

}