#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tesina.h"

struct ast *newast(int nodetype, struct ast *l, struct ast *r)
{

    struct ast *a = malloc(sizeof(struct ast));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = nodetype;
    a->l = l;
    a->r = r;

    return a;
}

struct ast *newnum(double d)
{

    struct numval *a = malloc(sizeof(struct numval));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'D';
    a->number = d;

    return (struct ast *)a;
}

struct ast *newString(char *string)
{

    struct stringVal *a = malloc(sizeof(struct stringVal));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'S';
    a->string = string;

    return (struct ast *)a;
}

struct ast *newref(struct var *vr)
{

    struct ref *a = malloc(sizeof(struct asgn));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'R';
    a->var = vr;

    return (struct ast *)a;
}

struct ast *newGet(struct var *vr, int c)
{

    struct get *a = malloc(sizeof(struct get));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'G';
    a->getVal = NULL;
    char *si = "\"Si\"";
    char *no = "\"No\"";

    switch (c)
    {
    case 1:
        a->getVal = vr->paziente.cf;
        break;
    case 2:
        a->getVal = vr->paziente.esitoTamp;
        break;
    case 3:
        a->getVal = vr->paziente.dataTamp;
        break;
    case 4:
        a->getVal = vr->paziente.regione;
        break;
    case 5:
        a->getVal = vr->paziente.isRicoverato ? si : no;
        break;
    default:
        a->getVal = "Not found";
        break;
    }

    return (struct ast *)a;
}

struct ast *newasgn(struct var *vr, struct ast *v)
{

    struct asgn *a = malloc(sizeof(struct asgn));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = '=';
    a->var = vr;
    a->v = v;

    return (struct ast *)a;
}

struct ast *newCmp(int cmptype, struct ast *l, struct ast *r)
{

    struct ast *a = malloc(sizeof(struct ast));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = '0' + cmptype;
    a->l = l;
    a->r = r;

    return a;
}

struct ast *newCond(int nodetype, struct ast *cond, struct ast *then, struct ast *els)
{

    struct cond *a = malloc(sizeof(struct cond));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = nodetype;
    a->cond = cond;
    a->then = then;
    a->els = els;

    return a;
}

struct ast *newPaziente(int nodetype, struct ast *cf, struct ast *dataTamp, struct ast *esitoTamp, struct ast *regione, struct ast *isRicoverato)
{

    struct paziente *a = malloc(sizeof(struct paziente));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    /* paziente3 = PAZIENTE("DGVMRC97P11G273M","11Set1997","Positivo","Sicilia",1) */
    /* paziente3 = PAZIENTE(CF,"11Marzo1997","Positivo","Lombardia",1) */
    a->nodetype = nodetype;
    a->cf = cf;
    a->dataTamp = dataTamp;
    a->esitoTamp = esitoTamp;
    a->regione = regione;
    a->isRicoverato = isRicoverato;

    return a;
}


