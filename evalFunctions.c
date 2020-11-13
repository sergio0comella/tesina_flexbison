#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tesina.h"

/* Funzione di valutazione dell'albero generale */
struct result eval(struct ast *a)
{

    struct result risultato;
    risultato.risD = 0;
    risultato.risS = NULL;
    risultato.risP.cf = NULL;

    switch (a->nodetype)
    {
    /* Numeri (double) */
    case 'D':
        risultato.risD = ((struct numval *)a)->number;
        break;

    /* Stringa */
    case 'S':
        risultato.risS = ((struct stringVal *)a)->string;
        break;

    /* Paziente */
    case 'P':
        risultato.risP.cf = eval(((struct paziente *)a)->cf).risS;
        risultato.risP.dataTamp = eval(((struct paziente *)a)->dataTamp).risS;
        risultato.risP.esitoTamp = eval(((struct paziente *)a)->esitoTamp).risS;
        risultato.risP.regione = eval(((struct paziente *)a)->regione).risS;
        risultato.risP.isRicoverato = ((struct numval *)(((struct paziente *)a)->isRicoverato))->number;
        break;

    /* Get valori Paziente */
    case 'G':
        risultato.risS = ((struct get *)a)->getVal;
        break;

    /* Assegnamento */
    case '=':
    {
        struct result risAsgn = evalAsgn(a);

        if (risAsgn.risS == NULL && risAsgn.risP.cf == NULL)
        {
            risultato.risD = risAsgn.risD;
            break;
        }
        if (risAsgn.risS == NULL && risAsgn.risD == 0)
        {
            risultato.risP = risAsgn.risP;
            break;
        }
        if (risAsgn.risP.cf == NULL && risAsgn.risD == 0)
        {
            risultato.risS = risAsgn.risS;
            break;
        }
        break;
    }

    /* Reference */
    case 'R':
        if (((struct ref *)a)->var->varType == 'S')
        {
            risultato.risS = ((struct ref *)a)->var->string;
            break;
        }
        else
        {
            if (((struct ref *)a)->var->varType == 'P')
            {
                risultato.risP = ((struct ref *)a)->var->paziente;
                break;
            }
        }
        risultato.risD = ((struct ref *)a)->var->valore;
        break;

    /* IF */
    case 'I':
        if (eval(((struct cond *)a)->cond).risD != 0)
        {
            risultato = eval(((struct cond *)a)->then);
            break;
        }
        else
        {
            if (((struct cond *)a)->els == NULL)
            {
                break;
            }
            else
            {
                risultato = eval(((struct cond *)a)->els);
                break;
            }
        }

    /* WHILE */
    case 'W':
        while (eval(((struct cond *)a)->cond).risD != 0)
        {
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
        if ((eval(a->l).risS) != NULL)
        {
            risultato.risD = (int)(strcmp(eval(a->l).risS, eval(a->r).risS) == 0);
            break;
        }
        risultato.risD = evalExpr(a);
        break;

    case 'L':
        eval(a->l);
        eval(a->r);
        break;

    default:
        printf("Errore interno di valutazione - nodetype: %d", a->nodetype);
    }

    return risultato;
}

/* Funzione che valuta l'assegnamento di valori a variabili */
struct result evalAsgn(struct ast *a)
{

    struct result risultato;
    risultato.risD = 0;
    risultato.risS = NULL;
    risultato.risP.cf = NULL;

    struct result risAnnidato;
    risAnnidato.risD = 0;
    risAnnidato.risS = NULL;
    risAnnidato.risP.cf = NULL;

    risAnnidato = eval(((struct asgn *)a)->v);

    if (risAnnidato.risS == NULL && risAnnidato.risP.cf == NULL)
    {
        ((struct asgn *)a)->var->varType = 'D';
        risultato.risD = ((struct asgn *)a)->var->valore = eval(a->r).risD;
    }
    if (risAnnidato.risS == NULL && risAnnidato.risD == 0)
    {
        ((struct asgn *)a)->var->varType = 'P';
        risultato.risP = ((struct asgn *)a)->var->paziente = eval(a->r).risP;
    }
    if (risAnnidato.risP.cf == NULL && risAnnidato.risD == 0)
    {
        ((struct asgn *)a)->var->varType = 'S';
        risultato.risS = ((struct asgn *)a)->var->string = eval(a->r).risS;
    }

    return risultato;
}

/* Funzione che valuta espressioni numeriche */
double evalExpr(struct ast *a)
{

    double v;

    switch (a->nodetype)
    {
    /* Numeri (double) */
    case 'D':
        v = ((struct numval *)a)->number;
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
        if (v < 0)
            v = -v;
        break;
    case 'M':
        v = -eval(a->l).risD;
        break;

    case '1':
        v = (int)(eval(a->l).risD > eval(a->r).risD);
        break;
    case '2':
        v = (int)(eval(a->l).risD < eval(a->r).risD);
        break;
    case '3':
        v = (int)(eval(a->l).risD != eval(a->r).risD);
        break;
    case '4':
        v = (int)(eval(a->l).risD == eval(a->r).risD);
        break;
    case '5':
        v = (int)(eval(a->l).risD >= eval(a->r).risD);
        break;
    case '6':
        v = (int)(eval(a->l).risD <= eval(a->r).risD);
        break;
    default:
        break;
    }

    return v;
}