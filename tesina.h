extern int yylineno;
void yyerror(char *s, ...);

/* Varibile definita dall'utente */
struct var {
    char* nome;
    double valore;
    char *string;
};

#define NHASH 9997
struct var vartab[NHASH];

struct var *lookup(char *name);


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

/*costruzione AST*/
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);                         // D
struct ast *newString(char *string);                  // S
struct ast *newasgn(struct var *vr, struct ast *v);   // A
struct ast *newref(struct var* vr);                   // R 

/*Valutazione tramite ast*/
double eval(struct ast *);

/*cancellazione nodi*/
void treefree(struct ast *);


