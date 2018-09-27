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
access():

*/

#define int DEFAULT 100;


char* inputfile(char* filename) {
  File *fb;
  fb = fopen(("%c.txt",filename), "r")
  return fgetc(fb);
}

// Define allocates you memory and gives you a pointer for it, use: Variable's pointer = define(true); (given it is an int)
int* define(isint) {
  if (isint) {
    return malloc()
  }
  return malloc()
}

void main() {
  File *fb;

  //Statement.replace("C99","cc -std=c99 -Wall -pedantic -Werror")

  /*num variables*sizeof(variable) or DEFAULT*/
  if (/*size known*/) {
    for (int i; i < numofvariabletypes; i++) {
      variabletype = types[i];
      int *pointer = malloc(numvariable*sizeof(variabletype));
    }
  } else {
    int *pointer = malloc(DEFAULT);
  }

  fb = fopen("filename.txt", "r");
}
