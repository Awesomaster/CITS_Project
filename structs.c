#include "constants.c"

typedef struct actionline
{
    char *actionLine;
    struct next *next;
} ACTIONLINE;

typedef struct dependency
{
    char *name;
    struct next *next;
} DEPENDENCY;

typedef struct targetline
{
    char *name;
    int fileCharacteristics; //0th is i, 1st is n, 2nd is p, 3rd is s
    DEPENDENCY *dependencies;
    ACTIONLINE *actionLines;
    struct next *next;
} TARGETLINE;

typedef struct variable
{
    char *name;
    char *key;
    struct next *next;
} VARIABLE;

