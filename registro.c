#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tesina.h"
#include "parameters.h"

#define forEach(item, list) \
    for (item = list; item != NULL; item = item->pazienteSucc)

// Inserisce i pazienti estratti dal file esterno nel registro
int importToRegistro(struct pazienteDet paz, struct ast *a ) {
    //((struct importDet *)a)->varReg->registro

    PazienteDet pazTemp = paz;

    /*printf("\npazTemp.cf: %s\n", pazTemp.cf);
    printf("paz.dataTamp: %s\n", pazTemp.dataTamp);
    printf("recors[0].esitoTamp: %s\n", pazTemp.esitoTamp);
    printf("recors[0].regione: %s\n", pazTemp.regione);
    printf("paz.isRic: %d\n", pazTemp.isRicoverato);*/

    /* Caso in cui il registro sia vuoto */
    if (((struct importDet *)a)->varReg->registro.paziente.cf == NULL) {
            ((struct importDet *)a)->varReg->registro.occupato = 1;
            ((struct importDet *)a)->varReg->registro.paziente = pazTemp;
            //printf("\nENTRATO\n\n");
            return 1;
    }

    //printf("REGISTRO->paziente.cf: %s\n", ((struct importDet *)a)->varReg->registro.paziente.cf);

    /* Scorro la lista di pazienti per arrivare al primo posto disponibile e
     controllo che il paziente non sia già stato inserito nel registro */
    struct registro *lastPaziente = &((struct importDet *)a)->varReg->registro;
    while (lastPaziente->pazienteSucc != NULL) {
        /*if(!strcasecmp(lastPaziente->paziente.cf, pazTemp.cf)){
            return 0;       
       }*/

        lastPaziente = lastPaziente->pazienteSucc;
        //printf("LASTPAZIENTE->paziente.cf: %s\n", lastPaziente->paziente.cf);
    }

    /*controllo anche l'ultimo elemento che viene escluso dal while*/
    /*if(!strcasecmp(lastPaziente->paziente.cf, pazTemp.cf)){
        printf("ENTRATO ULTIMO STRCASE");
        return 0;
    }*/

    /* Inseriamo il paziente */
    struct registro *rTemp = malloc(sizeof(struct registro));
    rTemp->idReg = ((struct importDet *)a)->varReg->registro.idReg;
    rTemp->nodetype = NODE_REGISTRO;
    rTemp->paziente = pazTemp;
    rTemp->indice = lastPaziente->indice + 1;
    rTemp->pazienteSucc = NULL;
    lastPaziente->pazienteSucc = rTemp;

    /*risultato.risP = ((struct addPaziente*)a)->varReg->registro.paziente;*/
    return 1;   
}








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
        ((struct addPaziente *)a)->varReg->registro.occupato = 1;
        return 1;
    }

    //printf("registro->paziente.cf: %s\n", ((struct addPaziente *)a)->varReg->registro.paziente.cf);

    /* Scorro la lista di pazienti per arrivare al primo posto disponibile e
     controllo che il paziente non sia già stato inserito nel registro */
    struct registro *lastPaziente = &((struct addPaziente *)a)->varReg->registro;
    while (lastPaziente->pazienteSucc != NULL) {
        if(!strcasecmp(lastPaziente->paziente.cf, pazTemp.cf)){
            return 0;       
       }

        lastPaziente = lastPaziente->pazienteSucc;
        //printf("lastPaziente->paziente.cf: %s\n", lastPaziente->paziente.cf);
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
    rTemp->pazienteSucc = NULL;
    lastPaziente->pazienteSucc = rTemp;

    /*risultato.risP = ((struct addPaziente*)a)->varReg->registro.paziente;*/
    return 1;
}

//Restituisce il totale dei positivi in un dato registro
int getTotalePositivi(struct ast *a){
    
    int counter = 0;

    Registro *reg = &((struct numPazienti *)a)->varReg->registro;
    Registro *iter;
    /**
     * Se il primo paziente del registro ha il 
     * flag occupato == 0 allora il registro sarà vuoto.
     */
    if (reg->occupato == 0)
    {
        return counter;
    }
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

    //forEach che itera la lista dei pazienti
    Registro *reg = &((struct numPazienti *)a)->varReg->registro;
    Registro *iter;

    /**
     * Se il primo paziente del registro ha il 
     * flag occupato == 0 allora il registro sarà vuoto.
     */
    if (reg->occupato == 0)
    {
        return counter;
    }
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
    /**
     * Se il primo paziente del registro ha il 
     * flag occupato == 0 allora il registro sarà vuoto.
     */
    if (reg->occupato == 0)
    {
        return counter;
    }
    forEach(iter, reg){
        counter++;
    }
    return counter;
}


PazienteDet getPazienteByCf(struct ast *a){
    
    PazienteDet ris;
    ris.cf = NULL;

    char *cf = eval(((struct getPaziente *)a)->key).risS;

    Registro *reg = &((struct getPaziente *)a)->varReg->registro;
    Registro *iter;
    
    /**
     * Se il primo paziente del registro ha il 
     * flag occupato == 0 allora il registro sarà vuoto.
     */
    if(reg->occupato == 0) {
        return ris;
    }
    forEach(iter, reg){
        if (!strcasecmp(iter->paziente.cf, cf)){
            return iter->paziente;
        }
    }
    //printf("%s\n", ris.cf);

    return ris;
}

int getPositiviByFilter(struct ast *a){

    char *filter = eval(((struct numPositiviByFilter *)a)->filter).risS;

    /* regex che matcha le date*/
    char *regexDate = REGEX_DATA;
    char *regexCountry = REGEX_COUNTRY;

    int filterForDate = 0, filterForCountry = 0;
    if (match(filter, regexDate)){
        filterForDate = 1;
    }
    else if(match(filter, regexCountry)){
        filterForCountry = 1;
    }else{
        printf("Inserimento errato");
        return 0;
    }

    int counter = 0;
    Registro *reg = &((struct numPositiviByFilter *)a)->varReg->registro;
    Registro *iter;

    /**
     * Se il primo paziente del registro ha il 
     * flag occupato == 0 allora il registro sarà vuoto.
     */
    if (reg->occupato == 0)
    {
        return counter;
    }
    forEach(iter, reg){

        if (filterForDate && (!strcasecmp(iter->paziente.dataTamp, filter)) && (!strcasecmp(iter->paziente.esitoTamp, "\"positivo\"")))
        {
            counter += 1;
        }
        else if (filterForCountry && (!strcasecmp(iter->paziente.regione, filter)) && (!strcasecmp(iter->paziente.esitoTamp, "\"positivo\"")))
        {
            counter +=1;
        }
    }
    
    if(counter == 0){
        printf("Nessun paziente trovato con i criteri ricercati.");
    }
    return counter;
}