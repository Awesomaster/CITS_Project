#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "constants.c"
#include "structs.h"
#include "actionLine.h"
#include "targetLine.h"
#include "variableLine.h"

int main(int argc, char **argv)
{
  FILE *inputfile;
  char line[MAX_CHAR];
  char *filename;

  // --- Optional Modifiers Start ---
  int opt;
  opterr = 0;
  int inpstrue = 0;
  while ((opt = getopt(argc, argv, OPTLIST)) != -1)
  {
    if (opt == 'C')
    {
      // Change the directory (using the next string) -C
      chdir(optarg);
    }
    else if (opt == 'f')
    {
      // Change the file (from default) -f
      filename = strdup(optarg);
    }
    else if (opt == 'i')
    {
      // Ignore unsuccessful termination of actions -i
      // Return of getopt is always 1
      inpstrue += 1000;
    }
    else if (opt == 'n')
    {
      // Print all action lines and dont -n
      // Instead of running, print
      inpstrue += 100;
    }
    else if (opt == 'p')
    {
      // -p
      inpstrue += 10;
    }
    else if (opt == 's')
    {
      // -s
      inpstrue += 1;
    }
    else
    {
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

  // --- START OF READING LINES ---
  // Read the file, line by line
  int lastline = 0; // Useful for actionLine
  VARIABLE *variables = malloc(sizeof(VARIABLE));
  TARGETLINE *wholeFile = malloc(sizeof(TARGETLINE));
  ACTIONLINE *actions = malloc(sizeof(ACTIONLINE));
  int currentLine = 0; // Integer used to store the current possition in wholeFile
  while (fgets(line, MAX_CHAR, inputfile) != NULL)
  {
    printf("%s", line);
    if (startsWithChar(line, '#'))
    {
      // Type Comment
      // Ignore this line
      lastline = 0; // Comment thus not useful for actionLines
      // printf("/---/ Above line is a comment thus provides no useful information (to a simple computer like me :D)\n");
    }
    else if (startsWithChar(line, '\t'))
    {
      // Type Action Line
      /*if (lastlinetype == targetline || action line) {
          run line through command terminal
      */

      if (lastline >= 1)
      {
        pushAction(line, actions);
        addActionLine(wholeFile, actions); // 
        // printf("\n/---/ This starts with a tab and thus is, is opperated over if it follows either an actionline or targetname\n");
        lastline += 1; // If a line after is also a target it will be linked
      }
    }
    else if (containsChar(line, ':'))
    {
      // Need new line since starting a targetLine
      currentLine += 1;

      // -- Seperating into multiple dependencies -- 
      char *dependencies = endingOfLine(line, ':');
      char *dependencyList[20]; // Used to store all the dependencies
      if (strcmp(dependencies, "") != 0)
      {
        int numDependencies = 0;
        char *dependency;
        char buf[50]; // Used for the max number of characters of a dependency

        strcpy(buf, dependencies);
        dependency = buf;
        for (int i = 0; buf[i] != '\0'; i++)
        {
          if (buf[i] == ' ')
          {
            buf[i] = '\0';
            dependencyList[numDependencies] = dependency;
            numDependencies++;
            dependency = buf + i + 1;
          }
        }
        if (dependency != NULL)
        {
          dependencyList[numDependencies] = dependency;
        }
        for (int i = 0; i < numDependencies + 1; i++)
        {
          // Check date last modified
          printf("%s\n", dependencyList[i]);
        }
      }
      // -- Seperating into multiple dependencies --
      pushLine(firstWord(line, ':'), NULL, dependencyList, inpstrue);
      ACTIONLINE *actions = NULL;

      printf("/---/ Above line is a target line\n");
      printf("/---/ Name: %s\n", wholeFile->name);
      lastline = 1;
    }
    else if (containsChar(line, '='))
    {
      // Need new line since starting a variableDefinition
      currentLine += 1;
      realloc(variables, (currentLine + 1) * sizeof(VARIABLE));

      // Type Variable Definition
      // Get the first bit, and every time $(first bit) is written, replace with second bit
      addVariable(variables, firstWord(line, '='), endingOfLine(line, '=')); // This places it on top of the stack
      fprintf(stdout, "/---/ Above line is a variable assignment, here we must assign the variables name (when in parenthesis starting with a $)\n");
      fprintf(stdout, "/---/ Name: %s, Value: %s\n", wholeFile[currentLine].name, wholeFile[currentLine].key);
      lastline = 0;
      
    }
    else
    {
      // To make sure we dont allow action lines to continue counting up
      lastline = 0;
    }
  }
  for (int i = 0; i < currentLine; i++)
  {
    printf("%i, %s, %s\n", i, wholeFile[i].name, wholeFile[i].key);
  }

  fclose(inputfile);
  return 0;
}