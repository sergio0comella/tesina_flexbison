#include <stdio.h>
#include "../headers/tesina.h"
#include "../headers/parameters.h"

void treefree(struct ast *a)
{

    if (a == NULL)
    {
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
        freeString((struct stringVal *)a);
        break;

    case NODE_DOUBLE:
        freeDouble((struct numVal *)a);
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
        freeAddPaziente((struct addPaziente *)a);
        break;

    case NODE_REFERENCE:
        freeRef((struct ref *)a);
        break;

    case NODE_GETPAZ:
        freeGetPaziente((struct getPaziente *)a);
        break;

    case NODE_PAZIENTE_FILTER:
        freePazienteFilter((struct numPositiviByFilter *)a);
        break;

    case NODE_NUMPAZ:
        freeNumPaz((struct numPazienti *)a);
        break;

    case NODE_NUMPOS:
        freeNumPos((struct numPositivi *)a);
        break;

    case NODE_NUMRIC:
        freeNumRic((struct numRicoverati *)a);
        break;

    default:
        printf("Errore interno di liberazione memoria\n");
    }
}

void freeNumPos(struct numPositivi *a)
{

    if (a == NULL)
    {
        return;
    }

    free(a);
}

void freeNumRic(struct numRicoverati *a)
{

    if (a == NULL)
    {
        return;
    }

    free(a);
}

void freeNumPaz(struct numPazienti *a)
{

    if (a == NULL)
    {
        return;
    }

    free(a);
}

void freePazienteFilter(struct numPositiviByFilter *a)
{

    if (a == NULL)
    {
        return;
    }

    treefree(a->filter);
    free(a);
}

void freeGetPaziente(struct getPaziente *a)
{

    if (a == NULL)
    {
        return;
    }

    treefree(a->key);
    free(a);
}

void freeRef(struct ref *a)
{

    if (a == NULL)
    {
        return;
    }

    free(a);
}

void freeDouble(struct numval *a)
{

    if (a == NULL)
    {
        return;
    }

    free(a);
}

void freeString(struct stringVal *a)
{

    if (a == NULL)
    {
        return;
    }

    free(a);
}

void freePaziente(struct paziente *a)
{

    if (a == NULL)
    {
        return;
    }

    treefree(a->cf);
    treefree(a->dataTamp);
    treefree(a->esitoTamp);
    treefree(a->isRicoverato);
    treefree(a->regione);
    free(a);
}

void freeRegistro(struct ast *a)
{

    if (a == NULL)
    {
        return;
    }

    free(a);
}

void freeAsgn(struct asgn *a)
{

    if (a == NULL)
    {
        return;
    }

    treefree(a->v);
    free(a);
}

void freePrint(struct print *a)
{

    if (a == NULL)
    {
        return;
    }

    treefree(a->val);
    free(a);
}

void freeGet(struct get *a)
{

    if (a == NULL)
    {
        return;
    }

    free(a);
}

void freeAddPaziente(struct addPaziente *a)
{

    if (a == NULL)
    {
        return;
    }

    treefree(a->paziente);
    free(a);
}