#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "../headers/tesina.h"
#include "../headers/parameters.h"

struct ast *newast(int nodetype, struct ast *l, struct ast *r)
{

    struct ast *a = malloc(sizeof(struct ast));

    if (!a)
    {
        printNotValidCommand("out of space");
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
        printNotValidCommand("out of space");
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
        printNotValidCommand("out of space");
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
        printNotValidCommand("out of space");
        exit(0);
    }

    a->nodetype = NODE_REFERENCE;
    a->var = vr;
    
    return (struct ast *)a;
}

struct ast *newGet(struct var *vr,int c)
{

    struct get *a = malloc(sizeof(struct get));

    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }


    a->nodetype = NODE_GET;
    a->varPaz = vr;
    a->getVal = c;


    return (struct ast *)a;
}

struct ast *newasgn(struct var *vr, struct ast *v)
{

    struct asgn *a = malloc(sizeof(struct asgn));

    if (!a)
    {
        printNotValidCommand("out of space");
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
        printNotValidCommand("out of space");
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
        printNotValidCommand("out of space");
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
        printNotValidCommand("out of space");
        exit(0);
    }

    /* paziente5 = PAZIENTE("DGVmrC11G273M","11-08-1997","Positivo","Calabria",1) */
    /*  */
    /* paziente1 = PAZIENTE(10,"10-09-1997","Negativo","Veneto",0)*/
    /* paziente4 = PAZIENTE("ffff","10-04-1997","Negativo","Lombardia",0) */
    
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
        printNotValidCommand("out of space");
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
        printNotValidCommand("out of space");
        exit(0);
    }

    /*if(var->varType != NODE_REGISTRO) {
      printNotValidCommand("NameError: Registro non istanziato");
      return newNodeError();
    }*/

    a->nodetype = NODE_ADD_PAZIENTE;
    a->varReg = var;
    a->paziente = paziente;

    return a;

}

struct ast *getPaziente(struct var* var, struct ast* codFis) {

    struct getPaziente *a = malloc(sizeof(struct getPaziente));

    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    /*if(var->varType != NODE_REGISTRO) {
      printNotValidCommand("NameError: Registro non istanziato");
      return newNodeError();
    }*/

    a->nodetype = NODE_GETPAZ;
    a->varReg = var;
    a->key = codFis;

    return a;

}

struct ast *numPazienti(struct var* var) {

    struct numPazienti *a = malloc(sizeof(struct numPazienti));

    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    /*if(var->varType != NODE_REGISTRO) {
      printNotValidCommand("NameError: Registro non istanziato");
      return newNodeError();
    }*/

    a->nodetype = NODE_NUMPAZ;
    a->varReg = var;

    return a;

}


struct ast *numPositivi(struct var* var) {

    struct numPositivi *a = malloc(sizeof(struct numPositivi));

    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    /*if(var->varType != NODE_REGISTRO) {
      printNotValidCommand("NameError: Registro non istanziato");
      return newNodeError();
    }*/

    a->nodetype = NODE_NUMPOS;
    a->varReg = var;

    return a;

}

struct ast *numRicoverati(struct var* var) {

    struct numRicoverati *a = malloc(sizeof(struct numRicoverati));

    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    /*if(var->varType != NODE_REGISTRO) {
      printNotValidCommand("NameError: Registro non istanziato");
      return newNodeError();
    }*/

    a->nodetype = NODE_NUMRIC;
    a->varReg = var;

    return a;

}

struct ast *numPositiviByFilter(struct var *var, struct ast* filter) {

    struct numPositiviByFilter *a = malloc(sizeof(struct numPositiviByFilter));

    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    /*if(var->varType != NODE_REGISTRO) {
      printNotValidCommand("NameError: Registro non istanziato");
      return newNodeError();
    }*/

    a->nodetype = NODE_PAZIENTE_FILTER;
    a->varReg = var;
    a->filter = filter;

    return a;

}

struct ast *newPrint(struct ast *val) {

    struct print *a = malloc(sizeof(struct print));

    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    a->nodetype = NODE_PRINT;
    a->val = val;
    
    return a;
}

struct ast *import(struct var *var, struct ast *fileUrl) {

    
    struct importDet *a = malloc(sizeof(struct importDet));

    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    /*if(var->varType != NODE_REGISTRO) {
      printNotValidCommand("NameError: Registro non istanziato");
      return newNodeError();
    }*/

    a->nodetype = NODE_IMPORT;
    a->varReg = var;
    a->fileUrl = fileUrl;

    
    return a;
}

struct ast *export(struct var *var) {

    struct exportDet *a = malloc(sizeof(struct exportDet));
    
    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    /*if(var->varType != NODE_REGISTRO) {
      printNotValidCommand("NameError: Registro non istanziato");
      return newNodeError();  
    }*/

    a->nodetype = NODE_EXPORT;
    a->varReg = var;

    return a;

}

struct ast* newMacro(struct var *vr, struct ast *v) {
    
    struct macro *a = malloc(sizeof(struct macro));

    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    a->noodetype = NODE_MACRO;
    a->var = vr;
    a->v = v;

    return a;
}

struct ast* newMacroCall(struct var *macrovar) {

    struct macroCall *a = malloc(sizeof(struct macroCall)); 
    
    if (!a)
    {
        printNotValidCommand("out of space");
        exit(0);
    }

    a->nodetype = NODE_MACRO_CALL;
    a->v = macrovar->macro;

    return a;

}

