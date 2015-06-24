#include <stdio.h>

#include "../include/memory.h"
#include "../include/tokenizing.h"

int tokenBuffSize = 0;

int delimCheck ( const char* fContents, int *prevTokPos)
{
  if ( (fContents[0] == ' ' ) || (fContents[0] == ';') || (fContents[0] == '\n') || (fContents[0] == '\t') ) //delimited by space
  {
    if ( (fContents[-1] != ' ') && (fContents[-1] != ';') && (fContents[-1] != '\n') && (fContents[-1] != '\t') )
    {
     // *prevTokPos += 1;
      return 1;
    }
  }
  
  return 0;
}

void pushToken (TOK_STRUCT **tokens, const char *fContents, int len, char delimCh)
{
  static int count = 0;
  if ( count++ == 0)
    *tokens = get_space (*tokens, sizeof (TOK_STRUCT) );
  else
    get_space (*tokens, sizeof (TOK_STRUCT) );
  (*tokens + tokenBuffSize)->str = fContents;
  (*tokens + tokenBuffSize)->delimCh = delimCh;
  (*tokens + tokenBuffSize)->size = len;
  tokenBuffSize++;
}


TOK_STRUCT* tokenizing (const char *fContents, TOK_STRUCT **tokens)
{
  int prevTokPos = 0;
  char prevCh;
    
  for (int i = 0; fContents[i] != '\0'; i++)
  {
    if ( delimCheck( fContents + i, &prevTokPos ) ) 
    {
      pushToken( tokens, fContents + prevTokPos, i - prevTokPos, fContents[i]); 
      prevTokPos = i;
    }

    else if ( (fContents[i-1] == ' ' ) || (fContents[i-1] == ';') || (fContents[i-1] == '\n') || (fContents[i-1] == '\t') ) 
      prevTokPos++;
   
    prevCh = fContents[i];

  }
  
  return *tokens;
}

