#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"

// Do something with an variableLine

void addVariable(VARIABLE *variables, char *name, char *key, int nth);
void replaceVariables(char *line, VARIABLE *variables);