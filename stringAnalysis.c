#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// -------------------------- <Start Of String Analysis> ---------------------------
// Below we have a series of functions, startsWithChar, containsChar, firstWord and endingOfLine
// These are used to search through strings and find out what needs to be found

// Will likely be used for finding # on lines to remove comments
int startsWithChar(char *line, char c) {
    // Simple function made to tell if a line starts with a char c, if it returns 1, it is a comment, if it returns a 0, it is not a comment
    if (line[0] == c) {
        return 1;
    } else {
        return 0;
    }
}

// Will most likely be implimented for use of finding = and :
int containsChar(char *line, char c) {
    // Simple function made to tell if a line contains a char c, if it returns 1, it is a comment, if it returns a 0, it is not a comment
    char *str;
    str = strchr(line, c);
    if (str != NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Will find the first word in a line which is terminated by either whitespace or a defined character
char *firstWord(char *line, char c) {
    int i = 0;
    while (true) {
        if ((line[i] == c) || (line[i] == ' ')) {
            char *word;
            strncpy(word, line, i);
            word[i] = '\0';
            return word;
        }
        i++;
    }
    return "There either is no firstWord or there is an issue";
}

// Returns the word after a particular character
char *wordAfter(char *line, char c) {
    char *word = strchr(line, c);
    while (word[0] != ' ') {
        *word++;
    }
    return word;
}

// Returns everything past a certain character (removing unneccesary whitespace at the beginning)
char *endingOfLine(char *line, char c) {
    // Find the point at which the character occurs
    char *word = strchr(line, c);

    // Find start of statement (ignoring whitespace) (by pushing the pointer forward)
    while (word[0] == ' ' || word[0] == c) {
        *word++;
    }
    // !!_____________________Want to check the efficiency of this solution_____________________!!
    return word;
}

// Replaces all copies of key with value in line
char *replace(char *line, char *key, char *value) {
    return "Please get this working, replacing is literally half the project";
}

// -------------------------- < End Of String Analysis> ---------------------------