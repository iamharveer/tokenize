#include <stdlib.h>

void* get_space (void *this, int sz)
 {
   this = realloc ( this, sz );
   return this;
 }


