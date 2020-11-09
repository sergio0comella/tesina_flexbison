#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tesina.h"

struct ast *newast(int nodetype, struct ast *l, struct ast *r) {

    struct ast *a = malloc(sizeof(struct ast));

    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = nodetype;
    a->l = l;
    a->r = r;

    return a;

}

struct ast *newnum(double d) {

    struct numval *a = malloc(sizeof(struct numval));
    
    if(!a) {
        yyerror("out of space");
        exit(0);
    }

    a->nodetype = 'D';
    a->number = d;

    return (struct ast *)a;

}

double eval(struct ast *a) {

    double v;

    switch(a->nodetype) {
        case 'D': v = ((struct numval*)a)->number; break;

        case '+': v = eval(a->l) + eval(a->r); break;
        case '-': v = eval(a->l) - eval(a->r); break;
        case '*': v = eval(a->l) * eval(a->r); break;
        case '/': v = eval(a->l) / eval(a->r); break;
        case '|': v = eval(a->l); if(v < 0) v = -v; break;
        case 'M': v = -eval(a->l); break;
        default: printf("Errore interno di valutazione");
    }

    return v;
}

void treefree(struct ast *a) {

    switch(a->nodetype) {

        case '+':
        case '-':
        case '*':
        case '/':
            treefree(a->r);
        case 'M':
        case '|':
            treefree(a->l);

        case 'D': free(a); break;

        default: printf("Errore interno di liberazione memoria");
    }
}

void yyerror(char *s,...) {
    fprintf(stderr, "Errore generico\n");
}

int main(int argc, char const *argv[])
{
    printf("");
    return yyparse();

}