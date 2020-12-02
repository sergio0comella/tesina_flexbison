#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* getfield(char* line, int num)
{
    const char* tok;
    int counter = 1;
    char* tempLine = line;
    for (tok = strtok(tempLine, ";"); tok && *tok; tok = strtok(NULL, ";\n"))
    {
        printf("\nTOK=%s\n", tok);
        printf("counter=%d\n", counter);
        printf("num=%d\n", num);

        if(counter == num)
            return tok;
        counter = counter + 1;
    }
    return NULL;
}

int main()
{
    FILE* stream = fopen("test.csv", "r");

    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        const char *tok;
        int field = 1;
        for (tok = strtok(tmp, ";"); tok && *tok; tok = strtok(NULL, ";\n"))
        {
            if(field == 1)
                records.cf = tok;
             else if(fields == 2)
                record.dataTamp = tok
                ..
                ..
                ..   
            printf("TOK[%d]=%s\n", field, tok);
            field++;
            if(field > 4)
             field = 1;
        }
        
        //printf("Field 3 would be %s\n", getfield(tmp, 3));
        //printf("Field 2 would be %s\n", getfield(tmp, 2));
        //printf("Field 1 would be %s\n", getfield(tmp, 1));
        //printf("----\n");
        // NOTE strtok clobbers tmp
        free(tmp);
    }
}