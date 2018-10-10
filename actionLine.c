#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stringAnalysis.c>

// Do something with an actionLine

void actionLine(char* line, int iistrue, int nistrue, int pistrue, int sistrue) {
    int exitstatus = 0;
    if (iistrue) {
        exitstatus = 1;
    } 
    if (nistrue) {
        printf(line);
        //dont run lines
        exit(1);
    }
    if (pistrue) {
        //
    }
    if (sistrue) {
        //dont print anything!
    }
}