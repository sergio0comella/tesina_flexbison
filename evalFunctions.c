#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "tesina.h"
#include "parameters.h"


/* Funzione di valutazione dell'albero generale */
struct result eval(struct ast *a)
{

    struct result risultato;
    risultato.risD = 0;
    risultato.risS = NULL;
    risultato.risP.cf = NULL;
    risultato.risO.idReg = 0;
    risultato.risO.occupato = 0;
    risultato.flagPrint = 0;
    
    switch (a->nodetype)
    {

    /* Stampare un valore */
    case NODE_PRINT:
    {
        struct result print;
        print = eval(((struct print *)a)->val);

        if(print.risS != NULL) {
            printf("> %s\n", print.risS);
            risultato.flagPrint = 1;
            break;
        }

        if(print.risD != 0.0) {
            printf("> %4.4g\n\n", print.risD);
            risultato.flagPrint = 1;
            break;
        }

        printf("Argomento da stampare non valido\n\n");
        risultato.flagPrint = 1;
        break;
    }
    

    /* Numeri (double) */
    case NODE_DOUBLE:
        risultato.risD = ((struct numval *)a)->number;
        break;

    /* Stringa */
    case NODE_STRING:
        risultato.risS = ((struct stringVal *)a)->string;
        break;

    /* Paziente */
    case NODE_PAZIENTE:{
        char *dataTamp = eval(((struct paziente *)a)->dataTamp).risS;
        char *regexDate = REGEX_DATA;
        if (!match(dataTamp, regexDate)){
            yyerror("Errore\n");
            risultato.risS = ("Formato data errato. Formato valido: dd-mm-yyyy.\n");
            break;
        }
        risultato.risP.cf = eval(((struct paziente *)a)->cf).risS;
        risultato.risP.dataTamp = dataTamp;
        risultato.risP.esitoTamp = eval(((struct paziente *)a)->esitoTamp).risS;
        risultato.risP.regione = eval(((struct paziente *)a)->regione).risS;
        risultato.risP.isRicoverato = ((struct numval *)(((struct paziente *)a)->isRicoverato))->number;
        break;
    }
    /* Get valori Paziente */
    case NODE_GET:
        risultato.risS = ((struct get *)a)->getVal;
        break;
    
    /* Inizializzazione registro */
    case NODE_REGISTRO:
        risultato.risO.idReg = createUID();
        risultato.risO.occupato = 0;
        break;

    /* Aggiunta di un paziente al registro */
    case NODE_ADD_PAZIENTE:
        if(addPazienteToRegistro(a)){
            risultato.risS = "Paziente aggiunto con successo";
        }else{
            risultato.risS = "Paziente già inserito in questo registro";
        }
        break;

    /* Estrazione di un paziente dal registro dato il codice fiscale */
    case NODE_GETPAZ:
    {
        if(getPazienteByCf(a).cf == NULL) {
            risultato.risS = "Paziente non trovato";
        } else {
            risultato.risP = getPazienteByCf(a);
        }
        break;
        
    } 

    /* Ottenre il numero di pazienti positivi per regione o per data */
    case NODE_PAZIENTE_FILTER:
        risultato.risD = getPositiviByFilter(a);
        break;

    /* Ottenere il numero di pazienti di un registro */
    case NODE_NUMPAZ:
        risultato.risD = getPazientiTotali(a);
        break;

    /* Ottenere il numero di pazienti positivi*/
    case NODE_NUMPOS:
        risultato.risD = getTotalePositivi(a);
        break;

    /* Ottenere il numero di pazienti ricoverati */
    case NODE_NUMRIC:
        risultato.risD = getTotaleRicoverati(a);
        break;

    /* Importare dati da file esterno */
    case NODE_IMPORT: 
    {    
        int result = startImportToRegistro(a);
        if(result > 0){
            risultato.risS = "Dati importati correttamente.";
        }else{
            risultato.risS = "Errore nell'import dei dati.";
        }
        break;
    }
    /* Export su file*/
    case NODE_EXPORT:
    {
        int result = exportRegistroToFile(a);
        if(result > 0){
            risultato.risS = "Dati esportati correttamente";
        }else{
            risultato.risS = "Errore nell'export dei dati";
        }
        break;
    }

    /* Assegnamento */
    case NODE_EQUAL:
    {
        struct result risAsgn = evalAsgn(a);

        if (risAsgn.risD != 0) {
            risultato.risD = risAsgn.risD;
            break;
        } if (risAsgn.risS == NULL && risAsgn.risD == 0 && risAsgn.risO.idReg == 0) {
            risultato.risP = risAsgn.risP;
            break;
        } if (risAsgn.risP.cf == NULL && risAsgn.risD == 0 && risAsgn.risO.idReg == 0) {
            risultato.risS = risAsgn.risS;
            break;
        } if (risAsgn.risO.idReg != 0) {
            risultato.risO.idReg = risAsgn.risO.idReg;
            break;
        }
        break;
    }

    /* Reference */
    case NODE_REFERENCE:
        if (((struct ref *)a)->var->varType == 'S')
        {
            risultato.risS = ((struct ref *)a)->var->string;
            break;
        }

        if (((struct ref *)a)->var->varType == 'P')
        {
            risultato.risP = ((struct ref *)a)->var->paziente;
            break;
        }

        if (((struct ref *)a)->var->varType == 'O')
        {
            risultato.risO = ((struct ref *)a)->var->registro;
            break;
        }
        
        risultato.risD = ((struct ref *)a)->var->valore;
        break;

    /* IF */
    case NODE_IF:
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
    case NODE_WHILE:
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
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
        {
        struct result ris;
        ris = evalExpr(a);
        if(findType(ris) == 1) {
            risultato.risD = ris.risD;
            break;
        }
        risultato.risS = ris.risS;
        break;
        }
    case NODE_SEQOP:
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
    risultato.risO.idReg = 0;

    struct result risAnnidato;
    risAnnidato.risD = 0;
    risAnnidato.risS = NULL;
    risAnnidato.risP.cf = NULL;
    risAnnidato.risO.idReg = 0;

    risAnnidato = eval(((struct asgn *)a)->v);

    if (risAnnidato.risD != 0) 
    {
        ((struct asgn *)a)->var->varType = NODE_DOUBLE;
        risultato.risD = ((struct asgn *)a)->var->valore = eval(a->r).risD;
    }

    if (risAnnidato.risS == NULL && risAnnidato.risD == 0 && risAnnidato.risO.idReg == 0) 
    {
        ((struct asgn *)a)->var->varType = NODE_PAZIENTE;
        risultato.risP = ((struct asgn *)a)->var->paziente = eval(a->r).risP;
    }

    if (risAnnidato.risP.cf == NULL && risAnnidato.risD == 0 && risAnnidato.risO.idReg == 0)
    {
        ((struct asgn *)a)->var->varType = NODE_STRING;
        risultato.risS = ((struct asgn *)a)->var->string = eval(a->r).risS;
    }

    if (risAnnidato.risO.idReg != 0) {
        ((struct asgn *)a)->var->varType = NODE_REGISTRO;
        risultato.risO.idReg = ((struct asgn *)a)->var->registro.idReg = eval(a->r).risO.idReg;
    }

    return risultato;
}

/* Funzione che valuta espressioni numeriche */
struct result evalExpr(struct ast *a)
{

    struct result risExpr;
    risExpr.risS = NULL;
    risExpr.risD = 0;
    risExpr.risP.cf = NULL;
    risExpr.risO.idReg = 0;
    risExpr.flagPrint = 0;

    struct result risLeft;
    risLeft.risD = NaN;
    struct result risRight;

    /* Numeri (double)
    case 'D':
        v = ((struct numval *)a)->number;
        printf("v inside evalExpr: %f", v);
        break;
    */


   switch (a->nodetype)
   {
    
   case 'M':
        risLeft = eval(a->l);
        if (findType(risLeft) == 1) {
            risExpr.risD = -risLeft.risD;
            break;
        }
        risExpr.risD = 0;
        break;

   case '+':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = risRight.risD + risLeft.risD;
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {

            //rimuove l'ultimo carattere della stringa (")
            int size = strlen(risLeft.risS); 
            risLeft.risS[size - 1] = '\0';
            //rimuovo il primo carattere della stringa (")
            memmove(risRight.risS, risRight.risS + 1, strlen(risRight.risS));

            risExpr.risS = strcat(risLeft.risS,risRight.risS);
            break;
        }
        risExpr.risD = 0;
        break;
   
   case '-':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = risLeft.risD - risRight.risD;
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = strlen(risLeft.risS) - strlen(risRight.risS);
            break;
        }
        risExpr.risD = 0;
        break;

    case '*':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = risRight.risD * risLeft.risD;
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = strlen(risLeft.risS) * strlen(risRight.risS);
            break;
        }
        risExpr.risD = 0;
        break;


    case '/':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = risLeft.risD / risRight.risD;
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = strlen(risLeft.risS) / strlen(risRight.risS);
            break;
        }
        risExpr.risD = 0;
        break;
    
    case '|':
        risLeft = eval(a->l);
        if (findType(risLeft) == 1) {
            if (risLeft.risD < 0) {
                risExpr.risD = -risLeft.risD;
            } else {
                risExpr.risD = risLeft.risD;
            }
            break;
        }
        risExpr.risD = 0;
        break;
    
    case '1':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = (int)(risLeft.risD > risRight.risD);
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = (int)(strlen(risLeft.risS) > strlen(risRight.risS));
            break;
        }
        /*if (left == 4 && right == 4) {

        }*/
        risExpr.risD = 0;
        break;
    
    case '2':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = (int)(risLeft.risD < risRight.risD);
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = (int)(strlen(risLeft.risS) < strlen(risRight.risS));
            break;
        }
        /*if (left == 4 && right == 4) {

        }*/
        risExpr.risD = 0;
        break;
    
    case '3':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = (int)(risLeft.risD != risRight.risD);
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = (int)strcmp(risLeft.risS,risRight.risS);
            break;
        }
        /*if (left == 4 && right == 4) {

        }*/
        risExpr.risD = 0;
        break;
    case '4':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = (int)(risLeft.risD == risRight.risD);
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = (int)(!strcmp(risLeft.risS,risRight.risS));
            break;
        }
        /*if (left == 4 && right == 4) {

        }*/
        risExpr.risD = 0;
        break;
    case '5':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = (int)(risLeft.risD >= risRight.risD);
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = (int)(strlen(risLeft.risS) >= strlen(risRight.risS));
            break;
        }
        /*if (left == 4 && right == 4) {

        }*/
        risExpr.risD = 0;
        break;
    case '6':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = (int)(risLeft.risD <= risRight.risD);
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = (int)(strlen(risLeft.risS) <= strlen(risRight.risS));
            break;
        }
        /*if (left == 4 && right == 4) {

        }*/
        risExpr.risD = 0;
        break;

   default:
       break;
   }
   
   return risExpr;

}
