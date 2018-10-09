#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stringAnalysis.c>

#define MAXCHAR 1000
#define ARGMAX 1

// -------------------------- < Start Of Main > -----------------------------------

int main(int argc, char **argv) {
  FILE *inputfile;
  char line[MAXCHAR];
  char *input;
  char* filename;
  char *dependencyList[] = {"-C", "-f", "-i", "-n", "-p", "-s"};

  if ((argc-1) >= ARGMAX) {
    input = argv[argc-1];
    // Dependences are 1 to (argc-2)
    for (int i = 0; i < argc-1; i++) {
      if (strcmp(argv[i], dependencyList[0])) {
        chdir(argv[i+1]);
      } else if (strcmp(argv[i], dependencyList[0])) {
        
      }
    }
  } else {
    printf("You have entered %i argument/s when you require at least %i", argc-1, ARGMAX);
    return 1;
  }

  if (strcmp(input,"1") == 0) {
    filename = "C:\\Users\\Josh\\Desktop\\inputfile.txt";
  } else {
    filename = input;
  }
  
   //"C:\\Users\\Josh\\Desktop\\inputfile.txt";

  inputfile = fopen(filename, "r");
  // Check file is valid (and openning was successful)
  if (inputfile == NULL) {
    printf("Could not open file %s",filename);
    return 1;
  }

  // Read the file, line by line
  while (fgets(line, MAXCHAR, inputfile) != NULL) {
    printf("%s", line);
    if (startsWithChar(line, '#')) {
      // Type Comment
      // Ignore this line
      printf("Above line is a comment thus provides no useful information (to a simple computer like me :D)\n");
    } else if (containsChar(line,':')) {
      // Type Target Line
      // DONT KNOW
      char* targetname;
      char* targetvalue;
      targetname = firstWord(line, ':');
      targetvalue = endingOfLine(line, ':');
      printf("Above line is a target line");
      printf("Name: %s, Value: %s\n", targetname, targetvalue);
    } else if (containsChar(line, '=')) {
      // Type Variable Definition
      // Get the first bit, and every time $(first bit) is written, replace with second bit
      char* variablename;
      char* variablevalue;
      variablename = firstWord(line, '=');
      variablevalue = endingOfLine(line, '=');
      printf("Above line is a variable assignment, here we must assign the variables name (when in parenthesis starting with a $)\n");
      printf("Name: %s, Value: %s\n", variablename, variablevalue);
    } else if (startsWithChar(line, '\t')) {
      // Type Action Line
      /*if (lastlinetype == targetline || action line) {
          run line through command terminal
      */
      printf("This starts with a tab and thus is, is opperated over if it follows either an actionline or targetname\n");
    }
  }

  fclose(inputfile);
  return 0;
}

// -------------------------- < End Of Main > -------------------------------------
