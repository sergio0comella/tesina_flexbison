#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "parameters.h"
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

    a->nodetype = NODE_REFERENCE;
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

    if(vr->paziente.cf == NULL) {
      yyerror("Paziente non istanziato"); 
    }

    a->nodetype = NODE_GET;
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

    a->nodetype = NODE_EQUAL;
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


    /* paziente3 = PAZIENTE("DGVmrC97P11G273M","11/08/1997","Positivo","Sicilia",1) */
    /* paziente5 = PAZIENTE("DGV73M","11Set1997","Positivo","Sicilia",1) */
    /* */
    /* paziente4 = PAZIENTE("ffff","11Marzo1997","Negativo","Lombardia",0) */
    
    a->nodetype = nodetype;
    a->cf = cf;
    a->dataTamp = dataTamp;
    a->esitoTamp = esitoTamp;
    a->regione = regione;
    a->isRicoverato = isRicoverato;

    return a;
}

struct ast *newRegistro(int nodetype) {

    struct ast *a = malloc(sizeof(struct ast));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = nodetype;

    return a;

    /*registro1 = REGISTRO() */
}

struct ast *addPaziente(struct var* var, struct ast* paziente)
{

    struct addPaziente *a = malloc(sizeof(struct addPaziente));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    if(var->registro.idReg == 0) {
      yyerror("Registro non istanziato");
      exit(0);  
    }

    a->nodetype = NODE_ADD_PAZIENTE;
    a->varReg = var;
    a->paziente = paziente;

    return a;

}

struct ast *getPaziente(struct var* var, struct ast* codFis) {

    struct getPaziente *a = malloc(sizeof(struct getPaziente));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    if(var->registro.idReg == 0) {
      yyerror("Registro non istanziato");  
    }

    a->nodetype = NODE_GETPAZ;
    a->varReg = var;
    a->key = codFis;

    return a;

}

struct ast *numPazienti(struct var* var) {

    struct numPazienti *a = malloc(sizeof(struct numPazienti));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    if(var->registro.idReg == 0) {
      yyerror("Registro non istanziato");  
    }

    a->nodetype = NODE_NUMPAZ;
    a->varReg = var;

    return a;

}


struct ast *numPositivi(struct var* var) {

    struct numPositivi *a = malloc(sizeof(struct numPositivi));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    if(var->registro.idReg == 0) {
      yyerror("Registro non istanziato");  
    }

    a->nodetype = NODE_NUMPOS;
    a->varReg = var;

    return a;

}

struct ast *numRicoverati(struct var* var) {

    struct numRicoverati *a = malloc(sizeof(struct numRicoverati));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    if(var->registro.idReg == 0) {
      yyerror("Registro non istanziato");  
    }

    a->nodetype = NODE_NUMRIC;
    a->varReg = var;

    return a;

}

struct ast *numPositiviByFilter(struct var *var, struct ast* filter) {

    struct numPositiviByFilter *a = malloc(sizeof(struct numPositiviByFilter));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    if(var->registro.idReg == 0) {
      yyerror("Registro non istanziato");  
    }

    a->nodetype = NODE_PAZIENTE_FILTER;
    a->varReg = var;
    a->filter = filter;

    return a;

}

