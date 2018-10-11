#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "actionLine.h"

void targetLine(char* line);

// Do something with a targetLine

void targetLine(char* line) {
    char *target = firstWord(line, ':');
    char *dependencies = endingOfLine(line, ':');
    if (strcmp(dependencies, "") != 0) {
        char* dependencyList[20]; // Used to store all the dependencies 
        int numDependencies = 0;
        char* dependency;
        char buf[50]; // Used for the max number of characters of a dependency

        strcpy(buf,dependencies);
        dependency = buf;
        for (int i = 0; buf[i] != '\0'; i++) {
            if (buf[i] == ' ') {
                buf[i] = '\0';
                dependencyList[numDependencies] = dependency;
                numDependencies++;
                dependency = buf+i+1;
            }
        }
        if (dependency != NULL) {
            dependencyList[numDependencies] = dependency;
        }
        for (int i=0; i < numDependencies+1; i++) {
            // Check date last modified
            printf("%s\n", dependencyList[i]);
        }
    }
}