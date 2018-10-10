#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "variableLine.h" // Includes targetLine.c which includes actionLine/c which includes stringAnalysis/c

#define MAXCHAR 1000
#define ARGMAX 1

int main(int argc, char **argv) {
  FILE *inputfile;
  char line[MAXCHAR];
  char *filename;
  char *dependencyList[] = {"-C", "-f", "-i", "-n", "-p", "-s"};
  int itrue = 0;
  int ntrue = 0;
  int ptrue = 0;
  int strue = 0;

  if ((argc-1) >= ARGMAX) {
    // input = argv[argc-1];
    // Dependences can be all
    for (int i = 0; i < argc-1; i++) {
      if (strcmp(argv[i], dependencyList[0])==0) {
        // Change the directory (using the next string) -C
        chdir(argv[i+1]);
      } else if (strcmp(argv[i], dependencyList[1])==0) {
        // Change the file (from default) -f
        filename = argv[i+1];
      } else if (strcmp(argv[i], dependencyList[2])==0) {
        // Ignore unsuccessful termination of actions -i
        // Return of getopt is always 1
        itrue = 1;
      } else if (strcmp(argv[i], dependencyList[3])==0) {
        // Print all action lines and dont -n
        // Instead of running, print
        ntrue = 1;
      } else if (strcmp(argv[i], dependencyList[4])==0) {
        // -p
        ptrue = 1;
      } else if (strcmp(argv[i], dependencyList[5])==0) {
        // -s
        strue = 1;
      }
    }
  } else {
    printf("You have entered %i argument/s when you require at least %i", argc-1, ARGMAX);
    return 1;
  }
  
   //"C:\\Users\\Josh\\Desktop\\inputfile.txt";

  inputfile = fopen(filename, "r");
  // Check file is valid (and openning was successful)
  if (inputfile == NULL) {
    printf("Could not open file %s",filename);
    return 1;
  }

  // Read the file, line by line
  int lastline = 0; // Useful for actionLine
  while (fgets(line, MAXCHAR, inputfile) != NULL) {
    printf("%s", line);
    if (startsWithChar(line, '#')) {
      // Type Comment
      // Ignore this line
      lastline = 0; // Comment thus not useful for actionLines
      printf("/---/ Above line is a comment thus provides no useful information (to a simple computer like me :D)\n");
    } else if (containsChar(line,':')) {
      // Type Target Line
      char* targetname;
      char* targetvalue;
      targetname = firstWord(line, ':');
      targetvalue = endingOfLine(line, ':');
      printf("/---/ Above line is a target line\n");
      printf("/---/ Name: %s, Value: %s\n", targetname, targetvalue);
      targetLine(line);
      lastline = 1;
    } else if (startsWithChar(line, '\t')) {
      // Type Action Line
      /*if (lastlinetype == targetline || action line) {
          run line through command terminal
      */
      //actionLine(line, itrue, ntrue, ptrue, strue);
      if (lastline == 1) {
        actionLine(line, itrue, ntrue, ptrue, strue);
      }
      printf("/---/ This starts with a tab and thus is, is opperated over if it follows either an actionline or targetname\n");
      lastline = 1;
    } else if (containsChar(line, '=')) {
      // Type Variable Definition
      // Get the first bit, and every time $(first bit) is written, replace with second bit
      
      char* variablename;
      char* variablevalue;
      variablename = firstWord(line, '=');
      variablevalue = endingOfLine(line, '=');
      printf("/---/ Above line is a variable assignment, here we must assign the variables name (when in parenthesis starting with a $)\n");
      printf("/---/ Name: %s, Value: %s\n", variablename, variablevalue);
      lastline = 0;
    }
  }

  fclose(inputfile);
  return 0;
}