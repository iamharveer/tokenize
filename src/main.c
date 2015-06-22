#include <stdio.h>
#include "../include/memory.h"

char* readFile (int, char**); //defined in readFile.c

int main(int argc, char *argv[])
{
  // pointer returned by readFile is a dynamic pointer
  // allocated via memalloc in readFile fxn, remember to
  // free it after its use.
  char *fContents = readFile(argc, argv);

  printf ("%s", fContents);

  return 0;
}
