extern int yylineno;
void yyerror(char *s, ...);

/* Paziente details, contiene i dettagli del paziente memorizzati dalla variabile */
struct pazienteDet {
    char *cf;
    char *dataTamp;
    char *esitoTamp;
    char *regione;
    int isRicoverato;   
};

/* Risultati delle valutizioni delle espressioni memorizzate nei rispettivi tipi */
struct result {
    double risD;
    char *risS;
    struct pazienteDet risP;
};


/* Varibile definita dall'utente che può essere un Double, una String o un Paziente o un Registro */
struct var {
    int varType;        //D -> Double, S -> String, P -> Paziente, R -> Registro
    char* nome;
    double valore;
    char *string;
    struct pazienteDet paziente;
    struct registro *registro;
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

/* Struttura per il tipo paziente */
struct paziente {
    int nodetype;
    struct ast *cf;
    struct ast *dataTamp;
    struct ast *esitoTamp;
    struct ast *regione;
    struct ast *isRicoverato;
};

/* Registro dei pazienti ovvero una lista 
struct registro {
    int nodetype;
    int indice;
    struct paziente *paziente;
    struct registro *pazSucc;
};*/

/*costruzione AST*/
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);                                                                           // D
struct ast *newString(char *string);                                                                    // S
struct ast *newasgn(struct var *vr, struct ast *v);                                                     // A
struct ast *newref(struct var* vr);                                                                     // R 
struct ast *newCmp(int cmptype, struct ast *l, struct ast *r);                                          // 1-6 
struct ast *newCond(int nodetype, struct ast *, struct ast *, struct ast*);                             // I o W

//P
struct ast *newPaziente(int nodetype, struct ast *cf, struct ast *dataTamp,struct ast *esitoTamp, struct ast *regione, struct ast *isRicoverato);

/*cancellazione nodi*/
void treefree(struct ast *);

/* Analisi e manipolazione albero sintattico che si è costruito */
void processTree(int,struct ast *);
struct result eval(struct ast *a);
double evalExpr(struct ast *a);
struct result evalAsgn(struct ast *a);

