#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
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
            
            variabile->varType = NULL;
            variabile->nome = strdup(nome);
            variabile->valore = 0;
            variabile->string = NULL;
            variabile->paziente.cf = NULL;
            variabile->paziente.dataTamp = NULL;
            variabile->paziente.esitoTamp = NULL;
            variabile->paziente.regione = NULL;
            variabile->paziente.isRicoverato = 0;
            variabile->registro = NULL;

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

struct ast *newCmp(int cmptype, struct ast *l, struct ast *r) {
    
    struct ast *a = malloc(sizeof(struct ast));
    
    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = '0' + cmptype;
    a->l = l;
    a->r = r;

    return a;
}

struct ast *newCond(int nodetype, struct ast *cond, struct ast *then, struct ast *els) {

    struct cond *a = malloc(sizeof(struct cond));

    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = nodetype;
    a->cond = cond;
    a->then = then;
    a->els = els;

    return a;
}

struct ast *newPaziente(int nodetype, struct ast *cf, struct ast *dataTamp,struct ast *esitoTamp, struct ast *regione, struct ast *isRicoverato) {
    
    struct paziente *a = malloc(sizeof(struct paziente));

    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    /* paziente1 = paziente("c","a","b","d",0) */
    a->nodetype = nodetype;
    a->cf = cf;

    a->dataTamp = dataTamp;
    a->esitoTamp = esitoTamp;
    a->regione = regione;
    a->isRicoverato = isRicoverato;

    return a;

}


void processTree(int print,struct ast *a) {

    struct result risultato = eval(a);

    if(print == 'P') {
        if(risultato.risS != NULL) {
            printf("= %s\n", risultato.risS);
        } else {
            if(risultato.risP.cf != NULL) {
                printf("\nDATI PAZIENTE %s \n -Data tampone: %s \n -Esito tampone %s\n -Regione %s\n" 
                        "-Ricoverato (1->si) %d\n", risultato.risP.cf,risultato.risP.dataTamp,
                        risultato.risP.esitoTamp, risultato.risP.regione, risultato.risP.isRicoverato);

            } else {
               printf("= %4.4g\n", risultato.risD);
            }

        }
    }
}

struct result eval(struct ast *a) {

    struct result risultato;
    risultato.risD = 0;
    risultato.risS = NULL;
    risultato.risP.cf = NULL;

    struct result risAsgn;

    switch(a->nodetype) {
        /* Numeri (double) */
        case 'D': risultato.risD = ((struct numval*)a)->number; break; 

        /* Stringa */
        case 'S': risultato.risS = ((struct stringVal *)a)->string; break;

        /* Paziente */
        case 'P': 
            risultato.risP.cf = ((struct stringVal *)(((struct paziente *)a)->cf))->string;
            risultato.risP.dataTamp = ((struct stringVal *)(((struct paziente *)a)->dataTamp))->string;
            risultato.risP.esitoTamp = ((struct stringVal *)(((struct paziente *)a)->esitoTamp))->string;
            risultato.risP.regione = ((struct stringVal *)(((struct paziente *)a)->regione))->string;
            risultato.risP.isRicoverato = ((struct numval *)(((struct paziente *)a)->isRicoverato))->number;
            break;
        
        /* Assegnamento */
        case '=': {
           struct result risAsgn = evalAsgn(a);
            
            if(risAsgn.risS != NULL && risAsgn.risP.cf != NULL) {
                    risultato.risD = risAsgn.risD;
                    break;
            }
            if(risAsgn.risS != NULL && risAsgn.risD == 0) {
                    risultato.risP = risAsgn.risP;
                    break;
            }
            if(risAsgn.risP.cf != NULL && risAsgn.risD == 0) {
                    risultato.risS = risAsgn.risS;
                    break;
            }
        }

        /* Reference */
        case 'R':
            if(((struct ref *)a)->var->varType == 'S') {
                risultato.risS = ((struct ref *)a)->var->string;
                break;
            } else {
                if(((struct ref *)a)->var->varType == 'P') {
                    risultato.risP = ((struct ref *)a)->var->paziente;
                    break;
                } 
            }     
            risultato.risD = ((struct ref *)a)->var->valore; 
            break;
        
        /* IF */
        case 'I':
            if(eval(((struct cond *)a)->cond).risD != 0) {
                risultato = eval(((struct cond *)a)->then);
                break;
            } else {
                if(((struct cond *)a)->els == NULL) {
                    break;
                } else {
                    risultato = eval(((struct cond *)a)->els);
                    break;
                }
            }
        
        /* WHILE */
        case 'W':
            while(eval(((struct cond *)a)->cond).risD != 0) {
                risultato = eval(((struct cond *)a)->then);
            }
            break;


        /* Operazioni aritmetiche */
        case '+': 
        case '-': 
        case '*': 
        case '/': 
        case '|': 
        case 'M':
            risultato.risD = evalExpr(a);
            break;

        /* Operazioni di comparazione */
        case '1':
        case '2':
        case '3':
        case '5':
        case '6':
            risultato.risD = evalExpr(a);
            break;
        /* Confronto tra due stringhe */
        case '4':
            if((eval(a->l).risS) != NULL) {
                if(!strcmp(eval(a->l).risS,eval(a->r).risS)) {
                    risultato.risD = 1;
                    break;
                } else {
                    risultato.risD = 0;
                    break;
                }               
            }
            risultato.risD = evalExpr(a);
            break;
        
        
        case 'L': eval(a->l); eval(a->r);
            break;

        default: printf("Errore interno di valutazione - nodetype: %d", a->nodetype);
    }

    return risultato;
}

struct result evalAsgn(struct ast *a) {

    struct result risultato;
    risultato.risD = 0;
    risultato.risS = NULL;
    risultato.risP.cf = NULL;

    switch(((struct asgn *)a)->v->nodetype) { 
        case 'S':
            ((struct asgn *)a)->var->varType = 'S';
            risultato.risS = ((struct asgn *)a)->var->string = eval(a->r).risS;
            break;
        
        case 'D':
            ((struct asgn *)a)->var->varType = 'D'; 
            risultato.risD = ((struct asgn *)a)->var->valore = eval(a->r).risD; 
            break;
        
        case 'P':
            ((struct asgn *)a)->var->varType = 'P';
            risultato.risP =  ((struct asgn *)a)->var->paziente = eval(a->r).risP;
            break;
        
        default:
            yyerror("Assegnamento non riuscito");
            break;
    }

    return risultato;
}




double evalExpr(struct ast *a) {            //Funzione che valuta espressioni numeriche

    double v;
    
    switch (a->nodetype)
    {
        /* Numeri (double) */
        case 'D': 
            v = ((struct numval*)a)->number; 
            break; 


        case '+': 
            v = eval(a->l).risD + eval(a->r).risD; 
            break;
        case '-': 
            v = eval(a->l).risD - eval(a->r).risD; 
            break;
        case '*': 
            v = eval(a->l).risD * eval(a->r).risD; 
            break;
        case '/': 
            v = eval(a->l).risD / eval(a->r).risD; 
            break;
        case '|': 
            v = eval(a->l).risD; 
            if(v < 0) v = -v; 
            break;
        case 'M': 
            v = -eval(a->l).risD; 
            break;

        
        case '1':
            if(eval(a->l).risD > eval(a->r).risD) {
                v = 1;
                break;
            } else {
                v = 0;
                break;
            }
        case '2':
            if(eval(a->l).risD < eval(a->r).risD) {
                v = 1;
                break;
            } else {
                v = 0;
                break;
            }
        case '3':
            if(eval(a->l).risD != eval(a->r).risD) {
                v = 1;
                break;
            } else {
                v = 0;
                break;
            }
        case '4':
            if(eval(a->l).risD == eval(a->r).risD) {
                v = 1;
                break;
            } else {
                v = 0;
                break;
            }
        case '5':
            if(eval(a->l).risD >= eval(a->r).risD) {
                v = 1;
                break;
            } else {
                v = 0;
                break;
            }
        case '6':
            if(eval(a->l).risD <= eval(a->r).risD) {
                v = 1;
                break;
            } else {
                v = 0;
                break;
            }

    
    default:
        break;
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