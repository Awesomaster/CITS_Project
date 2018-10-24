typedef struct S_actionline
{
    char *actionLine;
    struct S_actionline *next;
} ACTIONLINE;

typedef struct S_dependency
{
    char *name;
    struct S_dependency *next;
} DEPENDENCY;

typedef struct S_targetline
{
    char *name;
    int fileCharacteristics; //0th is i, 1st is n, 2nd is p, 3rd is s
    DEPENDENCY *dependencies;
    ACTIONLINE *actionLines;
    struct S_targetline *next;
} TARGETLINE;

typedef struct
{
    char *name;
    char *key;
} VARIABLE;
