/*
The text lines within bake's specification file are of four forms -
1. lines beginning with a '#' character are comment lines and may be ignored;
2. lines providing variable definitions which may be expanded within later lines of the file;
3. lines defining targets and optional dependencies used to determine if a target needs 'rebuilding'; and
4. lines defining actions, immediately following target lines, providing shell commands to be executed to 'rebuild' each target. Note that action lines do not necessarily create or rebuild a (physical) file named after the target, and a target might never exist as a file.
*/

// We have to do a series of regex tests to find terms

// We need to handle # (this indicates a comment, thus all characters until the next \n should be ignored)
// We need to handle variables, thus we should use an array/map of variable names and memory pointers, indicated by NAME = ...
// We need to handle targets and dependences. Check for rebuild, if needed, otherwise ignore it, indicated by TARGET : ...
// We need to excecute shell commands which are actions indicated by a \t at the beginning of the new line

/*
Helping notes
For system and file calls:
- access(), fopen(), fgets(), strdup(), fclose()

Variable Definitions:
- calloc(), realloc(), strdup(), getpid(), getppid(), getcwd(), rand(), getenv()

Target liens:
- ccalloc(), realloc(), strdup(), stat(), fork(), execl(), wait(), fopen(), fgets(), fclose(), mktime(), gettimeofday(), strptime()

Action lines:
- getenv(), calloc(), realloc(), strdup(), fork(), execl(), wait()

Invocation and command-line options
- getopt(), chdir(), exit()

Dictionary of meanings:
# int access(char *path, int mode): Return type int; Tells if you have access (r,w,x) of a particular path (amode = R_OK (read), W_OK (write), X_OK (execute), F_OK (exists))
# File *fopen(char *path, int mode): Returns type File*; e.g. fopen("C:/Users/josh/Desktop/CITS2002.c", "r") will return the file located at that position and allow you to read it
# char *fgets(char *str, int size, File *file): Returns type string (char*); Reads size-1 chars from the file and places them into the char* s; stops if it reads EOF; if it hits a \n, stores it and stops; terminating null byte stored at end
# char *strdup(char *str): Return type char*; Returns a pointer to a new place in the memory (found my malloc), and places a duplicate of the string
# int fclose(File *file): Return type int; Returns 0 when complete, otherwise it just flushes the stream pointed to by 'file'
# void *calloc(size_t nummemb, size_t size): Return type pointer (void*); Allocates memory for nummenb elements of size bytes in sequence and returns a pointer to the starting byte
# void *realloc(void *ptr, size_t size): Return type pointer (void*); Changes the size of the memory block pointed to by ptr and makes it size bytes, if new size > old, new memory will not be initialised
# pid_t getpid(void): Returns type process id; Returns the process ID of the calling process
# pid_t getppid(void): Returns type process id; Returns the process ID of the calling process's parent process
# char *getcwd(char *str, size_t size): Return type string (char*); Copies an absolute pathname of the current working directory to a string str of length size, if work directory name length > size, return an error
# int rand(void): Returns type int; Returns a pseudo-random number from [0,RAND_MAX], (RAND_MAX is something weird but its at least 32767 for some reason)
#_Dont_Know_# char *getenv(char* name): Returns type string (char*): Searches environment list for the environment variable 'name' and returns a pointer to the value string corresponding to it
 - Only example I can thing of is using PATH, and thus it should return all of the values assocated with path for your computer/program?
#_Dont_Know_# int stat(char *path, struct stat *buf): Return tupe int; Stats the file pointed to by path and fills in buf
# pid_t fork(void): Returns pid_t (in parent returns childs PID (or -1 if not success), in child returns 0 (if successful)); Creates a child process by duplicating the parent process, the new process is an exact duplicate of the parent bar a few things i.e. has a different PID
#_Dont_Know_# int execl(char *path, char* arg,...): Dont really get
# pid_t wait(int *status): Returns type pid; Suspends excecution of calling process until one of its children terminate
# time_t mktime(struct tm *tm): Returns type time_t; Converts broken down time (see struct tm*), expressed as local time, to calender time representation
#_Dont_Know_# int gettimeofday(struct timeval *tv, struct timezone *tz): Return type int; I dont really get what it returns because it says 0 for success??
#_Dont_Know_# char *strptime(char *s, char *format, struct tm *tm): Return type string;
# int getopt(int argc, char * const argv[], char *optstring): Return type int; Parses the command line argument
# int chdir(char *path): Return type int; Changes the current working directory to path
# void exit(int status): Ends the program returning with the exit status 'status'

SELF RESEARCH: (Useful functions)
char *strchr(char *str, char c): Finds the first instance of a char c in the string and returns a pointer to that char otherwise returns NULL (we can use this to find either the : or the = in a line to tell if it is a variable definition or something else...)
 - Returns the rest of the string after (and including) the char c (we can use this to find what we what the variable to be defined by)
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXCHAR 1000
#define ARGMAX 1


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
char *firstWord(char *line, char c) {\
  int i = 0;
  while (true) {
    if ((line[i] == c) || (line[i] == ' ')) {
      char *word;
      strncpy(word,line,i);
      word[i] = '\0';
      return word;
    }
    i++;
  }
    return "There either is no firstWord or there is an issue";
}

// Returns the word after a particular character
char *wordAfter(char *line, char c) {
  char* word = strchr(line, c);
  while (word[0] != ' ') {
    *word++;
  }
  return word;
}

// Returns everything past a certain character (removing unneccesary whitespace at the beginning)
char *endingOfLine(char *line, char c) {
  // Find the point at which the character occurs
  char* word = strchr(line, c);

  // Find start of statement (ignoring whitespace) (by pushing the pointer forward)
  while (word[0] == ' ' || word[0] == c) {
    *word++;
  }
  // !!_____________________Want to check the efficiency of this solution_____________________!!
  return word;
}

// Replaces all copies of key with value in line
char *replace(char *line, char *key, char *value) {

}

// -------------------------- < End Of String Analysis> ---------------------------
//
//
// -------------------------- < Start Of Main > -----------------------------------

int main(int argc, char **argv) {
  FILE *inputfile;
  char line[MAXCHAR];
  char *input;
  char* filename;
  char *dependencyList[] = {"-C", "-f", "-i", "-n", "-p", "-s"};
  
  if ((argc-1) >= ARGMAX) {
    input = argv[argc-1];
    // Dependences are 1-(argc-2)
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
      //if (lastlinetype == targetline || action line) {
        //run line through command terminal
      //}
      printf("This starts with a tab and thus is, is opperated over if it follows either an actionline or targetname\n");
    }
  }

  fclose(inputfile);
  return 0;
}

// -------------------------- < End Of Main > -------------------------------------
