#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "structs.h"
#include "constants.c"

void pushTargetLine(TARGETLINE *wholeFile, char *name, DEPENDENCY *dependencies, int fileCharacteristics)
{
    TARGETLINE *targline = calloc(1, sizeof(TARGETLINE));

    if (targline == NULL)
    {
        fprintf(stderr, "Error in pushing new targetline with values %s\n", name);
        perror(__func__);
        exit(EXIT_FAILURE);
    }

    targline->name = name;
    targline->dependencies = dependencies;
    targline->fileCharacteristics = fileCharacteristics;
    targline->next = wholeFile;
    wholeFile = targline;
}