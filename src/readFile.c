#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/memory.h"
extern int errno;

const char* get_fName (int argc, char **argv)
{
  for (int i = 0; i < argc; i++)
  {
    if ( !strcmp (argv[i], "-f") )
      return argv[i+1];
  }

  fprintf (stderr, "Please specify filename followed by '-f'\n");
  return NULL;
}

char* readFile(int argc, char *argv[])
{
  const char *fName = get_fName(argc, argv);
  if (fName == NULL)
    return NULL;

  char *fContents = NULL;
  fContents = (char *) get_space (fContents, 96);
  
  if (fContents == NULL)
    fprintf (stderr, "ERROR: %s at line number = %d\n", "get_space returned NULL", __LINE__);
  
  errno = 0;
  int fd = open ( fName, O_RDONLY);
  
  if (fd == -1)
    fprintf (stderr, "ERROR: %s at line number = %d\n", "opening file", __LINE__);

  char *preserveF_ptr = fContents;
  ssize_t nBytesRead;

  while (1)
  {
    nBytesRead = read (fd, fContents, 96);

    if ( nBytesRead == 96)
      get_space (preserveF_ptr, 96);
      
    else
    {
      if ( fContents[nBytesRead] == '\0')
        break;
    }

    fContents += 96;
  }
  
  return preserveF_ptr;
}







