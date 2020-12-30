#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include "../headers/tesina.h"
#include "../headers/parameters.h"

#define forEach(item, list) \
    for (item = list; item != NULL; item = item->pazienteSucc)

/* Funzione per generare un ID casuale per il registro */
int createUID()
{
    srand(time(0));

    int uid = (int)(rand() + 1);
    return uid;
}

int addPazienteToRegistro(struct ast *a)
{
    /* Estraggo il paziente */
    struct pazienteDet pazTemp = eval(((struct addPaziente *)a)->paziente).risP;

    if (pazTemp.cf == NULL) {
        printNotValidCommand("NameError: Paziente non istanziato\n");
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
        printNotValidCommand("GenericError: Filtro non valido\n");
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
        printf("\033[1;33m");
        printf("Warning: Nessun paziente trovato con i criteri ricercati.");
        printf("\033[0m");
    }
    return counter;
}

int startImportToRegistro(struct ast *a){

    char *fileUrl = eval(((struct importDet *)a)->fileUrl).risS;
    //Registro reg = ((struct importDet *)a)->varReg->registro;

    /**
     * La stringa del filename arriva con gli apici. 
     * Pulisco la stringa dal primo e dall'ultimo carattere.
     */
    int i , len = strlen(fileUrl); 

    for(i=1;i<len-1;i++){ 
        fileUrl[i-1] = fileUrl[i]; 
    } 
    fileUrl[i-1] = '\0'; 

    int number;
    
    FILE *f;
    f = fopen(fileUrl, "r");

    if(!f) {
        printNotValidCommand("Problema lettura file\n");
        return 0;
    }

    struct pazienteDet records[1000];
    char line[1024];
    char *cf;
    char *esitoTamp;
    char *dataTamp;
    char *regione;
    int isRicoverato;
    int data = 0;

    while (fgets(line, 1024, f))
    {
        char* tmp = strdup(line);
        const char *tok;
        int field = 1;
        for (tok = strtok(tmp, ";"); tok && *tok; tok = strtok(NULL, ";\n")) 
        {
            switch (field)
            {
                case 1:
                    cf = strdup(tok);
                    break; 
                case 2:
                    dataTamp = strdup(tok);
                    break;
                case 3:
                    esitoTamp = strdup(tok);
                    break;
                case 4: 
                    regione = strdup(tok);
                    break;
                case 5: 
                    isRicoverato = atoi(strdup(tok));
                    break;
                default:
                    printNotValidCommand("Errore switch case records-tok");
            }

            field++;
            if(field > 5) 
            {
                records[data].cf = cf;
                records[data].dataTamp = dataTamp;
                records[data].esitoTamp = esitoTamp;
                records[data].regione = regione;
                records[data].isRicoverato = isRicoverato; 
                data+=1;                             
                field = 1;
            }
        }

        free(tmp);
    }

    for(int j = 0; j < data; j++) {
        int r = importToRegistro(records[j],a);
        if( r == 0) {
            printf("\033[1;33m");
            printf("Warning: Codice fiscale già presente ( %s )\n", records[j].cf);
            printf("\033[0m");
        }
    }

    return 1;
}
// Inserisce i pazienti estratti dal file esterno nel registro
int importToRegistro(struct pazienteDet paz, struct ast *a ) {
    //((struct importDet *)a)->varReg->registro

    PazienteDet pazTemp = paz;

    /* Caso in cui il registro sia vuoto */
    if (((struct importDet *)a)->varReg->registro.paziente.cf == NULL) {
            ((struct importDet *)a)->varReg->registro.occupato = 1;
            ((struct importDet *)a)->varReg->registro.paziente = pazTemp;
            //printf("\nENTRATO\n\n");
            return 1;
    }

    /* Scorro la lista di pazienti per arrivare al primo posto disponibile e
     controllo che il paziente non sia già stato inserito nel registro */
    struct registro *lastPaziente = &((struct importDet *)a)->varReg->registro;
    while (lastPaziente->pazienteSucc != NULL) {
        if(!strcasecmp(lastPaziente->paziente.cf, pazTemp.cf)){
            return 0;       
       }
        lastPaziente = lastPaziente->pazienteSucc;
    }

    if(!strcasecmp(lastPaziente->paziente.cf, pazTemp.cf)){
            return 0;       
    }

    /* Inseriamo il paziente */
    struct registro *rTemp = malloc(sizeof(struct registro));
    rTemp->idReg = ((struct importDet *)a)->varReg->registro.idReg;
    rTemp->nodetype = NODE_REGISTRO;
    rTemp->paziente = pazTemp;
    rTemp->indice = lastPaziente->indice + 1;
    rTemp->pazienteSucc = NULL;
    lastPaziente->pazienteSucc = rTemp;

    return 1;   
}

int exportRegistroToFile(struct ast *a){
    Registro *reg = &((struct exportDet *)a)->varReg->registro;

    char fileUrl[128];
    time_t now;
    struct tm tm_now;
    now = time(NULL);
    localtime_r(&now, &tm_now);

    strftime(fileUrl, sizeof(fileUrl), "export/export_registro_%Y%m%d%H%M.csv", &tm_now);

    FILE *f;
    f = fopen(fileUrl, "a");

    if (!f)
    {
        printNotValidCommand("Problema apertura file\n");
    }

    Registro *iter;

    forEach(iter, reg)
    {
        fprintf(
            f,
            "%s;%s;%s;%s;%d\n",
            iter->paziente.cf,
            iter->paziente.dataTamp,
            iter->paziente.esitoTamp,
            iter->paziente.regione,
            iter->paziente.isRicoverato);
    }

    fclose(f);
    return 1;
}

void stampaRegistro(struct registro risO)
{

    Registro *iter;
    struct registro *reg = &risO;
    int counter = 1;

    printf("\033[1;37m");
    printf("Rosso: Positivi - Verdi: Negativi");
    printf("\n------------------");
    printf("| REGISTRO |");
    printf("------------------\n");

    forEach(iter, reg)
    {
        printf("|");
        if (!strcasecmp(iter->paziente.esitoTamp, "\"positivo\""))
        {
            printf("\033[1;31m");
        }
        else
        {
            printf("\033[1;32m");
        }
        printf("%d.\t%-16s\t%s\n", counter, iter->paziente.cf, iter->paziente.dataTamp);
        printf("\033[0m");
        counter += 1;
    }
    printf("\033[1;37m");
    printf("------------------------------------------------\n\n");
    printf("\033[0m");
}

void stampaPaziente(struct pazienteDet risP)
{
    printf("\033[1;37m");
    printf("\n----------");
    printf("| DATI PAZIENTE |");
    printf("----------\n");
    printf("|Cod. Fiscale: %s\n", risP.cf);
    printf("|Data Tamp: %s\n", risP.dataTamp);
    printf("|Esito Tamp: %s\n", risP.esitoTamp);
    printf("|Regione: %s\n", risP.regione);
    printf("|Ricoverato: %s\n", risP.isRicoverato == 1 ? "Sì" : "No");
    printf("-------------------------------------\n\n");
    printf("\033[0m");
}