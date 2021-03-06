extern int yylineno;
void yyerror(char *s, ...);

/* Paziente details, contiene i dettagli del paziente memorizzati dalla variabile */
typedef struct pazienteDet {
    char *cf;
    char *dataTamp;
    char *esitoTamp;
    char *regione;
    int isRicoverato;   
} PazienteDet;

/* Registro dei pazienti ovvero una lista */ 
typedef struct registro {
    int nodetype;
    int idReg;
    int indice;
    int occupato; 
    struct pazienteDet paziente;
    struct registro *pazienteSucc;
} Registro;

/* Risultati delle valutizioni delle espressioni memorizzate nei rispettivi tipi */
struct result {
    double risD;
    char *risS;
    struct pazienteDet risP;
    struct registro risO;
    int flagPrint;
    int flagBoolean;
};

/* Varibile definita dall'utente che può essere un Double, una String o un Paziente o un Registro */
struct var {
    int varType;        //D ->Double, S ->String, P ->Paziente, O->Registro, M->Macro
    char* nome;
    double valore;
    char *string;
    struct pazienteDet paziente;
    struct registro registro;
    struct ast *macro;
};

#define NHASH 9997
struct var vartab[NHASH];

struct var *lookup(char *name);

/* Nodo generico dell'albero */
struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
};

/* Numeri */
struct numval {
    int nodetype;
    double number;
};

/* Stringhe */
struct stringVal {
    int nodetype;
    char *string;
};

/* Assegnamento */
struct asgn {
    int nodetype;                   /* = */
    struct var *var;                /* a cosa voglio assegnare */
    struct ast *v;                 /* valore */
};

/* Reference */
struct ref {
    int nodetype;
    struct var *var;
};

/* Struttura condizionale: IF o WHILE */
struct cond {
    int nodetype;       
    struct ast *cond;
    struct ast *then;
    struct ast *els;
};

/* Struttura per ottenere i dati del paziente chiesti dalla get */
struct get {
    int nodetype;
    struct var *varPaz;
    char *getVal;
};

/* Struttura per il tipo paziente */
struct paziente {
    int nodetype;
    struct ast *cf;
    struct ast *dataTamp;
    struct ast *esitoTamp;
    struct ast *regione;
    struct ast *isRicoverato;
};

/* Struttura per gestire l'aggiunta di un paziente a un registro */
struct addPaziente {
    int nodetype;
    struct var *varReg;  
    struct ast *paziente;
};

/* Struttura per ottenere un paziente da un registro dato il codice fiscale */
struct getPaziente {
    int nodetype;
    struct var *varReg; 
    struct ast *key;
};

/* Struttura per ottenre il numero di pazienti di un registro */
struct numPazienti {
    int nodetype;
    struct var *varReg; 
};

/* Struttura per ottenre il numero di positivi di un registro */
struct numPositivi {
    int nodetype;
    struct var *varReg; 
};

/* Struttura per ottenre il numero di ricoverati di un registro */
struct numRicoverati {
    int nodetype;
    struct var *varReg; 
};

/* Struttura per ottenre il numero di positivi in una data/regione di un registro */
struct numPositiviByFilter {
    int nodetype;
    struct var *varReg; 
    struct ast *filter;
};

/* Struttura per stampare un determinato valore val */
struct print {
    int nodetype;
    struct ast *val;
};

/* Struttura per importare dati da un file */
struct importDet {
    int nodetype;
    struct var *varReg;
    struct ast *fileUrl;
};

/* Struttura per esportare i dati */
struct exportDet {
    int nodetype;
    struct var *varReg;
};

/* Struttura per memorizzare le macro operazioni */
struct macro {
    int noodetype;
    struct var *var;
    struct ast *v;
};

struct macroCall {
    int nodetype;
    struct ast *v;
};

struct nodeError {
    int nodetype;
};

/*costruzione AST*/
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);                                                                           // D
struct ast *newString(char *string);                                                                    // S
struct ast *newasgn(struct var *vr, struct ast *v);                                                     // '='
struct ast *newref(struct var* vr);                                                                     // R 
struct ast *newCmp(int cmptype, struct ast *l, struct ast *r);                                          // 1-6 
struct ast *newCond(int nodetype, struct ast *, struct ast *, struct ast*);                             // I o W
struct ast *newGet(struct var *vr,int c);                                                               // G
//P
struct ast *newPaziente(int nodetype, struct ast *cf, struct ast *dataTamp,struct ast *esitoTamp, struct ast *regione, struct ast *isRicoverato);
//O
struct ast *newRegistro(int nodetype);
//E
struct ast *addPaziente(struct var* varReg, struct ast* paziente);
//T
struct ast *getPaziente(struct var* var, struct ast* codFis);
//Z
struct ast *numPazienti(struct var* var);
//B
struct ast *numPositivi(struct var* var);
//C
struct ast *numRicoverati(struct var* var);
//F
struct ast *numPositiviByFilter(struct var *var, struct ast *filter);
//H
struct ast *newPrint(struct ast *a);
//J
struct ast *import(struct var *var, struct ast *fileUrl);
//K
struct ast *export(struct var *var);
//M
struct ast* newMacro(struct var *vr, struct ast *v);
//A
struct ast* newMacroCall(struct var *macrovar);


/* Analisi e manipolazione albero sintattico che si è costruito */
void processTree(int,struct ast *);
void stampaRegistro(struct registro risO);
void stampaPaziente(struct pazienteDet risP);
void printNotValidCommand(char *s);
struct result eval(struct ast *a);
struct result evalExpr(struct ast *a);
struct result evalAsgn(struct ast *a);

/* Functions Registro */
int addPazienteToRegistro(struct ast *a);
int getTotalePositivi(struct ast *a);
int getTotaleRicoverati(struct ast *a);
int getPazientiTotali(struct ast *a);
int getPositiviByFilter(struct ast *a);
int findType(struct result risLeft);
PazienteDet getPazienteByCf(struct ast *a);

/* Tree free functions */
void treefree(struct ast *);
void freeString(struct stringVal *a);
void freeDouble(struct numval *a);
void freeRegistro(struct ast *a);
void freePaziente(struct paziente *a);
void freeAsgn(struct asgn *a);
void freePrint(struct print *a);
void freeGet(struct get *a);
void freeAddPaziente(struct addPaziente *a);
void freeRef(struct ref *a);
void freeNumPos(struct numPositivi *a);
void freeNumRic(struct numRicoverati *a);
void freeNumPaz(struct numPazienti *a);
void freePazienteFilter(struct numPositiviByFilter *a);
void freeGetPaziente(struct getPaziente *a);
void freeCond(struct cond * a);
void freeExport(struct exportDet *a);
void freeImport(struct importDet *a);
void freeMacro(struct macro *a);
void freeCallMacro(struct macroCall *a);
