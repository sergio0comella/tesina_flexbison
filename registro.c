#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tesina.h"
#include "parameters.h"

#define forEach(item, list) \
    for (item = list; item != NULL; item = item->pazienteSucc)

int addPazienteToRegistro(struct ast *a)
{

    /* Estraggo il paziente */
    struct pazienteDet pazTemp = eval(((struct addPaziente *)a)->paziente).risP;

    if (pazTemp.cf == NULL) {
        yyerror("Paziente non istanziato");
        exit(0);
    }

    /* Caso in cui il registro sia vuoto */
    if (((struct addPaziente *)a)->varReg->registro.paziente.cf == NULL) {
        ((struct addPaziente *)a)->varReg->registro.paziente = pazTemp;
        return 1;
    }

    /* Scorro la lista di pazienti per arrivare al primo posto disponibile */
    struct registro *lastPaziente = &((struct addPaziente *)a)->varReg->registro;
    while (lastPaziente->pazienteSucc != NULL) {
       if(!strcasecmp(lastPaziente->paziente.cf, pazTemp.cf)){
            return 0;       
       }
        lastPaziente = lastPaziente->pazienteSucc;
    }
    /*controllo anche l'ultimo elemento che viene escluso dal while*/
    if(!strcasecmp(lastPaziente->paziente.cf, pazTemp.cf)){
        return 0;
    }

    /* Inseriamo il paziente */
    struct registro *rTemp = malloc(sizeof(struct registro));
    rTemp->idReg = ((struct addPaziente *)a)->varReg->registro.idReg;
    rTemp->nodetype = NODE_REGISTRO;
    rTemp->paziente = pazTemp;
    rTemp->indice = lastPaziente->indice + 1;
    lastPaziente->pazienteSucc = rTemp;

    /*risultato.risP = ((struct addPaziente*)a)->varReg->registro.paziente;*/
    return 1;
}

//Restituisce il totale dei positivi in un dato registro
int getTotalePositivi(struct ast *a){
    
    int counter = 0;

    Registro *reg = &((struct numPazienti *)a)->varReg->registro;
    Registro *iter;
    forEach(iter, reg){
        if (!strcasecmp(iter->paziente.esitoTamp, "\"positivo\"")){
            counter += 1;
        }
    }

    return counter;
}

//Restituisce il totale dei ricoverati in un dato registro
int getTotaleRicoverati(struct ast *a) {
    int counter = 0;
/*
    struct registro *reg = &((struct numPazienti *)a)->varReg->registro;

    if (reg->paziente.cf == 0){
        return 0;
    }

    while (reg->pazienteSucc != NULL) {
        if (reg->paziente.isRicoverato == 1){
            counter += 1;
        }
        reg = reg->pazienteSucc;
    }

    if (reg->paziente.isRicoverato == 1){
        counter += 1;
    }

*/ //replaced with foreach
    Registro *reg = &((struct numPazienti *)a)->varReg->registro;
    Registro *iter;
    forEach(iter, reg)
    {
        if (iter->paziente.isRicoverato == 1){
            counter += 1;
        }
    }

    return counter;
}

//Restituisce il totale dei pazienti in un dato registro
int getPazientiTotali(struct ast *a){
    int counter = 0;

    Registro *reg = &((struct numPazienti *)a)->varReg->registro;
    Registro *iter;
    forEach(iter, reg){
        counter++;
    }
    return counter;
}


PazienteDet getPazienteByCf(struct ast *a){
    char *cf = eval(((struct getPaziente *)a)->key).risS;

    Registro *reg = &((struct getPaziente *)a)->varReg->registro;
    Registro *iter;
    forEach(iter, reg){
        if (!strcasecmp(iter->paziente.cf, cf)){
            return iter->paziente;
        }
    }
    
}