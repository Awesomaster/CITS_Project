#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "variableLine.h" // Includes targetLine.c which includes actionLine/c which includes stringAnalysis/c

#define MAXCHAR 1000
#define ARGMAX 1
#define OPTLIST "C:f:inps"

int main(int argc, char **argv)
{
  FILE *inputfile;
  char line[MAXCHAR];
  char *filename;

  // --- Optional Modifiers Start ---
  int opt;
  opterr = 0;
  int itrue = 0;
  int ntrue = 0;
  int ptrue = 0;
  int strue = 0;
  while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
    if (opt == 'C') {
      // Change the directory (using the next string) -C
      chdir(optarg);
    }
    else if (opt == 'f') {
      // Change the file (from default) -f
      filename = strdup(optarg);
    }
    else if (opt == 'i') {
      // Ignore unsuccessful termination of actions -i
      // Return of getopt is always 1
      itrue = 1;
    }
    else if (opt == 'n') {
      // Print all action lines and dont -n
      // Instead of running, print
      ntrue = 1;
    }
    else if (opt == 'p') {
      // -p
      ptrue = 1;
    }
    else if (opt == 's') {
      // -s
      strue = 1;
    }
    else {
      argc = -1;
    }
  }
  // --- Optional Modifiers End ---

  //"C:\\Users\\Josh\\Desktop\\inputfile.txt";

  inputfile = fopen(filename, "r");
  // Check file is valid (and openning was successful)
  if (inputfile == NULL)
  {
    printf("Could not open file %s", filename);
    return 1;
  }

  typedef struct
  {
    char *name;
    char *key;
    char **dependencies;
    char **actionLines;

    int *fileCharacteristics; //0th is i, 1st is n, 2nd is p, 3rd is s

  } LINE;

  // --- START OF READING LINES ---
  // Read the file, line by line
  int lastline = 0; // Useful for actionLine
  LINE *wholeFile = malloc(sizeof(LINE));
  int currentLine = 0; // Integer used to store the current possition in wholeFile
  while (fgets(line, MAXCHAR, inputfile) != NULL) {
    printf("%s", line);
    if (startsWithChar(line, '#')) {
      // Type Comment
      // Ignore this line
      lastline = 0; // Comment thus not useful for actionLines
      // printf("/---/ Above line is a comment thus provides no useful information (to a simple computer like me :D)\n");
    }
    else if (startsWithChar(line, '\t')) {
      // Type Action Line
      /*if (lastlinetype == targetline || action line) {
          run line through command terminal
      */
      if (lastline >= 1)
      {
        wholeFile[currentLine].actionLines[lastline-1] = line;
        // printf("\n/---/ This starts with a tab and thus is, is opperated over if it follows either an actionline or targetname\n");
        lastline += 1; // If a line after is also a target it will be linked
      }
    }
    else if (containsChar(line, ':'))
    {
      // Need new line since starting a targetLine
      currentLine += 1;
      realloc(wholeFile, (currentLine + 1) * sizeof(LINE));

      // Type Target Line
      wholeFile[currentLine].name = firstWord(line, ':');
      wholeFile[currentLine].key = endingOfLine(line, ':');

      printf("/---/ Above line is a target line\n");
      printf("/---/ Name: %s, Value: %s\n", wholeFile[currentLine].name, wholeFile[currentLine].key);
      lastline = 1;
    }
    else if (containsChar(line, '='))
    {
      // Need new line since starting a variableDefinition
      currentLine += 1;
      realloc(wholeFile, (currentLine + 1) * sizeof(LINE));

      // Type Variable Definition
      // Get the first bit, and every time $(first bit) is written, replace with second bit
      wholeFile[currentLine].name = firstWord(line, '=');
      wholeFile[currentLine].key = endingOfLine(line, '=');
      printf("/---/ Above line is a variable assignment, here we must assign the variables name (when in parenthesis starting with a $)\n");
      printf("/---/ Name: %s, Value: %s\n", wholeFile[currentLine].name, wholeFile[currentLine].key);
      lastline = 0;
    }
    else {
      // To make sure we dont allow action lines to continue counting up
      lastline = 0;
    }
  }
  for (int i = 0; i < currentLine; i++) {
    printf("%i, %s, %s\n", i, wholeFile[i].name, wholeFile[i].key);
  }
  
  fclose(inputfile);
  return 0;
}