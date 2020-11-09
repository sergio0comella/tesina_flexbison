extern int yylineno;
void yyerror(char *s, ...);

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

/*costruzione AST*/
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);

/*Valutazione tramite ast*/
double eval(struct ast *);

/*cancellazione nodi*/
void treefree(struct ast *);