#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "stringAnalysis.h"
#include "variableLine.h"

// Do something with a variableLine

void addVariable(VARIABLE *variables, char *name, char *key, int nth)
{
    variables = realloc(variables, sizeof(variables) + sizeof(name) + sizeof(key));
    variables[nth].name = strdup(name);
    variables[nth].key = strdup(key);
}

void replaceVariables(char *line, VARIABLE* variables)
{

}
