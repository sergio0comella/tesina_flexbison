#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tesina.h"

int main(int argc, char const *argv[])
{

    

    struct result risAsgn = evalAsgn();
    return 0;
}

struct result evalAsgn() {

    struct result risultato;
    risultato.risD = 0;
    risultato.risS = NULL;
    risultato.risP = NULL;

    return risultato;
}

