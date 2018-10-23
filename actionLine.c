#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "stringAnalysis.h"
#include "actionLine.h"

void pushAction(char *action, ACTIONLINE *wholeActionline)
{
    ACTIONLINE *actionline = calloc(1, sizeof(ACTIONLINE));
    if (actionline == NULL)
    {
        fprintf(stderr, "Error in pushing new actionline with value %s\n", action);
        perror(__func__);
        exit(EXIT_FAILURE);
    }

    actionline->actionLine = action;
    actionline->next = wholeActionline;
    wholeActionline = actionline;
}

void addActionLine(TARGETLINE *line, ACTIONLINE *actionLine)
{
    line->actionLines = realloc(line->actionLines, sizeof(actionLine));
    line->actionLines = actionLine;
}