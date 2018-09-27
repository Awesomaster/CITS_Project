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
#_Dont_Know_# int stat(char *path, struct stat *buf): Return tupe int; Stats the file pointed to by path and fills in buf
# pid_t fork(void): Returns pid_t (in parent returns childs PID (or -1 if not success), in child returns 0 (if successful)); Creates a child process by duplicating the parent process, the new process is an exact duplicate of the parent bar a few things i.e. has a different PID


*/

#define DEFAULT 100;


char* openfile(char* filename) {
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
