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
    {
      if ( argv[i+1] != NULL && argv[i+1] != 0)
        return argv[i+1];
      else
      {
        printf ("ERROR: Missing file name following '-f'\n");
        return NULL;
      }

    }
    
  }

  fprintf (stderr, "Please specify filename followed by '-f'\n");
  return NULL;
}

char* readFile(int argc, char *argv[])
{
  const char *fName = get_fName(argc, argv);
  if (fName == NULL)
    return NULL;

  errno = 0;
  int fd = open ( fName, O_RDONLY);
  
  if (fd == -1)
    fprintf (stderr, "ERROR: %s at line number = %d\n", "opening file", __LINE__);

  struct stat fStat = {0};
  if ( fstat( fd, &fStat) == -1)
    fprintf (stderr, "ERROR: %s at line number = %d\n", strerror(errno), __LINE__);
  
  char *fContents = get_space(NULL, fStat.st_size);
  if (fContents == NULL)
    fprintf (stderr, "ERROR: %s at line number = %d\n", "allocating space", __LINE__);
  
  int bytesToRead = fStat.st_size;  
  for (ssize_t bytesRead = 0; ; )
  {
     bytesRead = read (  fd, fContents, bytesToRead);
     if (bytesRead < bytesToRead)
     {
       bytesToRead -= bytesRead;
       fContents += bytesRead;
     }
     
     else
       break; 
  
  }

  return fContents;
}







