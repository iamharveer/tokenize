#include <stdio.h>
#include <stdlib.h>
#include "../include/memory.h"
#include "../include/tokenizing.h"

char* readFile (int, char**); //defined in readFile.c

int main(int argc, char *argv[])
{
  // pointer returned by readFile is a dynamic pointer
  // allocated via remalloc in readFile fxn, remember to
  // free it after use.
  char *fContents = readFile(argc, argv);
  if (fContents == NULL)
    return -1;

  TOK_STRUCT *tokens = NULL;
  tokenizing (fContents, &tokens);
  
  //tokenBuffSize is defined in declared as extern in tokenizing.h
  for (int i = 0; i < tokenBuffSize; i++)
  {
    int j = 0;

    while( (tokens+i)->size > j)
       printf ("%c", ((tokens+i)->str)[j++]);
    printf ("\n");
  }
  
  free(fContents);
  free(tokens);
  return 0;
}
