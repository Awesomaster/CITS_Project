#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "stringAnalysis.h"
#include "variableLine.h"

// Do something with an variableLine

void addVariable(VARIABLE *variables, char *name, char *key) {
    VARIABLE *variable = calloc(1, sizeof(VARIABLE));
    
    if (variable == NULL)
    {
        fprintf(stderr, "Error in pushing new line with values %s, %s\n", name, key);
        perror(__func__);
        exit(EXIT_FAILURE);
    }

    variable->name = name;
    variable->key = key;
    variable->next = variables;
    variables = variable;
}

char **removeVariable(VARIABLE *variables) {
    
}

void replaceVariables(char *line, VARIABLE *variables) {
    if (variables->next != NULL) {
        char *replaceable = strcat(strcat("$C",variables->name),")");
        if (strcmp(firstWord(line, ' '), replaceable) == 0) {

        }
        VARIABLE *tempVariables = calloc(1, sizeof(variables));
        memcpy(tempVariables, variables, sizeof(variables));

    }
}