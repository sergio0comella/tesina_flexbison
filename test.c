#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "tesina.h"

int main(int argc, char const *argv[])
{   
    char *str = strdup("AFFFF");

    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
        printf("char: %c\n", str[i]);
    }
}

