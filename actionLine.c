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
    actionline->nextAction = wholeActionline;
    wholeActionline = actionline;
}

void addActionLine(TARGETLINE *line, ACTIONLINE *actionLine)
{
    line->actionLines = realloc(line->actionLines, sizeof(actionLine));
    line->actionLines = actionLine;
}