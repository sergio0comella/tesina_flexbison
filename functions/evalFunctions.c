#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../headers/tesina.h"
#include "../headers/parameters.h"

/* Funzione di valutazione dell'albero generale */
struct result eval(struct ast *a)
{

    struct result risultato;
    risultato.risD = NaN;
    risultato.risS = NULL;
    risultato.risP.cf = NULL;
    risultato.risO.idReg = 0;
    risultato.risO.occupato = 0;
    risultato.flagPrint = 0;
    
    //printf("a->nodetype: %c\n", a->nodetype);

    switch (a->nodetype)
    {

    case NODE_CALLMACRO:
    {
        //printf("Entrato");
        risultato = eval(((struct macroCall *)a)->v);
        risultato.flagPrint = 1;
        
        break;
    }

    /* Generare una macro */
    case NODE_MACRO:
    {
        ((struct macro *)a)->var->varType = NODE_MACRO;
        ((struct macro *)a)->var->macro = ((struct macro *)a)->v;

        risultato.risD = 0;

        break;
    }

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

        if(print.risD != NaN) {
            printf("> %4.4g\n\n", print.risD);
            risultato.flagPrint = 1;
            break;
        }

        yyerror("Error: Argomento da stampare non valido\n\n");
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
        
        if(findType(eval(((struct paziente *)a)->cf)) != 2) {
            risultato.flagPrint = 1;

            yyerror("Error: CF wrong type\n");

            break;
        }

        if(findType(eval(((struct paziente *)a)->esitoTamp)) != 2) {
            risultato.flagPrint = 1;

            yyerror("Error: esitoTamp wrong type\n");

            break;
        }

        if(findType(eval(((struct paziente *)a)->regione)) != 2) {
            risultato.flagPrint = 1;

            yyerror("Error: regione wrong type\n");

            break;
        }

        if (!match(dataTamp, regexDate)){
            yyerror("Errore: Formato data errato. Formato valido: dd-mm-yyyy.\n");
            risultato.flagPrint = 1;
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
    {
        
        if(((struct get *)a)->varPaz->varType != NODE_PAZIENTE) {

            risultato.flagPrint = 1;

            yyerror("NameError: Paziente non istanziato\n");

            break;
        }
        
        char *si = "\"Si\"";
        char *no = "\"No\"";

        int c = ((struct get *)a)->getVal;
        risultato.risS = ((struct get *)a)->varPaz->paziente.cf;
        switch (c)
        {
        case 1:
            risultato.risS = ((struct get *)a)->varPaz->paziente.cf;
            break;
        case 2:
            risultato.risS = ((struct get *)a)->varPaz->paziente.esitoTamp;
            break;
        case 3:
            risultato.risS = ((struct get *)a)->varPaz->paziente.dataTamp;
            break;
        case 4:
            risultato.risS = ((struct get *)a)->varPaz->paziente.regione;
            break;
        case 5:
            risultato.risS = ((struct get *)a)->varPaz->paziente.isRicoverato ? si : no;
            break;
        default:
            risultato.flagPrint = 1;
            break;
        }
        
        break;
    }
    
    /* Inizializzazione registro */
    case NODE_REGISTRO:
        risultato.risO.idReg = createUID();
        risultato.risO.occupato = 0;
        break;

    /* Aggiunta di un paziente al registro */
    case NODE_ADD_PAZIENTE:

        if(findType(eval(((struct addPaziente *)a)->paziente)) != 3) {
            
            risultato.flagPrint = 1;

            yyerror("Error: Paziente wrong type\n");

            break;

        }

        if(((struct addPaziente *)a)->varReg->varType != NODE_REGISTRO) {

            risultato.flagPrint = 1;

            yyerror("NameError: Registro non istanziato\n");

            break;
        }

        if(addPazienteToRegistro(a)){
            risultato.risS = "Paziente aggiunto con successo\n";
        }else{
            
            risultato.flagPrint = 1;

            yyerror("Paziente già inserito in questo registro\n");
        }
        break;

    /* Estrazione di un paziente dal registro dato il codice fiscale */
    case NODE_GETPAZ:
    {   

        if(findType(eval(((struct getPaziente *)a)->key)) != 2) {
            risultato.flagPrint = 1;

            yyerror("Error: CF wrong type\n");

            break;
        }

        if(((struct getPaziente *)a)->varReg->varType != NODE_REGISTRO) {

            risultato.flagPrint = 1;

            yyerror("NameError: Registro non istanziato\n");

            break;
        }

        if(getPazienteByCf(a).cf == NULL) {

           risultato.flagPrint = 1;

           yyerror("Paziente non trovato\n");


        } else {
            risultato.risP = getPazienteByCf(a);
        }
        break;
        
    } 

    /* Ottenre il numero di pazienti positivi per regione o per data */
    case NODE_PAZIENTE_FILTER:

        if(findType(eval(((struct numPositiviByFilter *)a)->filter)) != 2) {
            risultato.flagPrint = 1;

            yyerror("Error: Filter wrong type\n");

            break;
        }

        if(((struct numPositiviByFilter *)a)->varReg->varType != NODE_REGISTRO) {
            
            risultato.flagPrint = 1;

            yyerror("NameError: Registro non istanziato\n");

            break;
        }

        risultato.risD = getPositiviByFilter(a);
        break;

    /* Ottenere il numero di pazienti di un registro */
    case NODE_NUMPAZ:

        if(((struct numPazienti *)a)->varReg->varType != NODE_REGISTRO) {
            
            risultato.flagPrint = 1;
            
            yyerror("NameError: Registro non istanziato\n");

            break;
        }

        risultato.risD = getPazientiTotali(a);
        break;

    /* Ottenere il numero di pazienti positivi*/
    case NODE_NUMPOS:
        
        if(((struct numPositivi *)a)->varReg->varType != NODE_REGISTRO) {

            risultato.flagPrint = 1;

            yyerror("NameError: Registro non istanziato\n");

            break;
        }

        risultato.risD = getTotalePositivi(a);
        break;

    /* Ottenere il numero di pazienti ricoverati */
    case NODE_NUMRIC:

        if(((struct numRicoverati *)a)->varReg->varType != NODE_REGISTRO) {

            risultato.flagPrint = 1;

            yyerror("NameError: Registro non istanziato\n");

            break;
        }

        risultato.risD = getTotaleRicoverati(a);
        break;

    /* Importare dati da file esterno */
    case NODE_IMPORT: 
    {    
        if(((struct importDet *)a)->varReg->varType != NODE_REGISTRO) {
            risultato.flagPrint = 1;
            
            yyerror("NameError: Registro non istanziato\n");
            
            break;
        }

        if(findType(eval(((struct importDet *)a)->fileUrl)) != 2) {
            risultato.flagPrint = 1;

            yyerror("Error: fileUrl wrong type\n");

            break;
        }

        int result = startImportToRegistro(a);
        if(result > 0){
            risultato.risS = "Dati importati correttamente.\n";
        }else{
            
            risultato.flagPrint = 1;

            yyerror("Errore nell'import dei dati.\n");
        }
        break;
    }
    
    /* Export su file*/
    case NODE_EXPORT:
    {
        if(((struct exportDet *)a)->varReg->varType != NODE_REGISTRO) {
            
            risultato.flagPrint = 1;
            
            yyerror("NameError: Registro non istanziato\n");
            
            break;
        }

        int result = exportRegistroToFile(a);
        if(result > 0){
            risultato.risS = "Dati esportati correttamente\n";
        }else{
            risultato.flagPrint = 1;
            yyerror("Errore nell'export dei dati\n");
        }
        break;
    }

    /* Assegnamento */
    case NODE_EQUAL:
    {
        struct result risAsgn = evalAsgn(a);

        int type = findType(risAsgn);

        if(type == 1) {
           risultato.risD = risAsgn.risD; 
           break;
        }

        if(type == 3) {
            risultato.risP = risAsgn.risP;
            break;
        }

        if(type == 2) {
           risultato.risS = risAsgn.risS;
           break; 
        }

        if(type == 4) {
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
    case NODE_NEGATIVE:
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
        {
        struct result ris;

        ris = evalExpr(a);
        if(ris.risS != NULL) {
            risultato.flagPrint = ris.flagPrint;
            risultato.risS = ris.risS;
            risultato.risD = ris.risD;
            break;
        }
        risultato.risD = ris.risD;
        risultato.flagPrint = ris.flagPrint;
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
    risultato.risD = NaN;
    risultato.risS = NULL;
    risultato.risP.cf = NULL;
    risultato.risO.idReg = 0;

    struct result risAnnidato;
    risAnnidato.risD = NaN;
    risAnnidato.risS = NULL;
    risAnnidato.risP.cf = NULL;
    risAnnidato.risO.idReg = 0;

    risAnnidato = eval(((struct asgn *)a)->v);

    int type = findType(risAnnidato);

    if(type == 1) {
        ((struct asgn *)a)->var->varType = NODE_DOUBLE;
        risultato.risD = ((struct asgn *)a)->var->valore = risAnnidato.risD;
    }

    if(type == 3) {
        ((struct asgn *)a)->var->varType = NODE_PAZIENTE;
        risultato.risP = ((struct asgn *)a)->var->paziente = risAnnidato.risP;
    }

    if(type == 2) {
        ((struct asgn *)a)->var->varType = NODE_STRING;
        risultato.risS = ((struct asgn *)a)->var->string = risAnnidato.risS;
    }

    if(type == 4) {
        ((struct asgn *)a)->var->varType = NODE_REGISTRO;
        risultato.risO.idReg = ((struct asgn *)a)->var->registro.idReg = risAnnidato.risO.idReg;
    }

    return risultato;
}

/* Funzione che valuta espressioni numeriche */
struct result evalExpr(struct ast *a)
{

    struct result risExpr;
    risExpr.risD = NaN;
    risExpr.risS = NULL;
    risExpr.risP.cf = NULL;
    risExpr.risO.idReg = 0;
    risExpr.risO.occupato = 0;
    risExpr.flagPrint = 0;

    struct result risLeft;
    risLeft.risD = NaN;
    struct result risRight;
    risRight.risD = NaN;

    /* Numeri (double)
    case 'D':
        v = ((struct numval *)a)->number;
        printf("v inside evalExpr: %f", v);
        break;
    */


   switch (a->nodetype)
   {
    
   case NODE_NEGATIVE:
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
            
            //Lavoro su elementi temporanei per non alterare i nodi
            int lenLeft = strlen(risLeft.risS);
            int lenRight = strlen(risRight.risS);

            char *left = (char *)malloc(lenLeft + 1);
            char *right = (char *)malloc(lenRight + 1);

            strcpy(left, risLeft.risS);
            strcpy(right, risRight.risS);

            //rimuove l'ultimo carattere della stringa (")
            left[lenLeft - 1] = '\0';
            //rimuovo il primo carattere della stringa (")
            memmove(right, right + 1, lenRight);

            risExpr.risS = strcat(left,right);
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
            int lenLeft = strlen(risLeft.risS);
            int lenRight = strlen(risRight.risS);
            //Restituisco sempre la differenze positive delle due stringhe
            if(lenLeft > lenRight){
                risExpr.risD = strlen(risLeft.risS) - strlen(risRight.risS);
            }else{
                risExpr.risD = strlen(risRight.risS) - strlen(risLeft.risS);
            }
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
            int temp = (int)(risLeft.risD > risRight.risD);
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            int temp = (int)(strlen(risLeft.risS) > strlen(risRight.risS));
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
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
            int temp = (int)(risLeft.risD < risRight.risD);
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            int temp = (int)(strlen(risLeft.risS) < strlen(risRight.risS));
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
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
            int temp = (int)(risLeft.risD != risRight.risD);
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            int temp = (int)strcmp(risLeft.risS, risRight.risS);
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
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
            int temp = (int)(risLeft.risD > risRight.risD);
            risExpr.risD = temp;
            char *ris = temp ? "true" : "false";
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            int temp = (int)(!strcmp(risLeft.risS, risRight.risS));
            risExpr.risD = temp;

            char *ris = temp ? "true" : "false";
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
            int temp = (int)(risLeft.risD >= risRight.risD);
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            int temp = (int)(strlen(risLeft.risS) >= strlen(risRight.risS));
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
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
            int temp = (int)(risLeft.risD <= risRight.risD);
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            int temp = (int)(strlen(risLeft.risS) <= strlen(risRight.risS));
            risExpr.risD = temp;
            risExpr.risS = temp ? "true" : "false";
            break;
        }
        /*if (left == 4 && right == 4) {

        }*/
        risExpr.risD = 0;
        break;
    
    case '7':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = (int)(risLeft.risD && risRight.risD);
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = (int)(strlen(risLeft.risS) && strlen(risRight.risS));
            break;
        }
        /*if (left == 4 && right == 4) {

        }*/
        risExpr.risD = 0;
        break;

    case '8':
        risLeft = eval(a->l);
        risRight = eval(a->r);
        if (findType(risLeft) == 1 && findType(risRight) == 1) {
            risExpr.risD = (int)(risLeft.risD || risRight.risD);
            break;
        }
        if (findType(risLeft) == 2 && findType(risRight) == 2) {
            risExpr.risD = (int)(strlen(risLeft.risS) || strlen(risRight.risS));
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
