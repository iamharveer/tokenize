typedef struct 
{
  char *str;
  int size;
  char delimCh;

} TOK_STRUCT;

TOK_STRUCT* tokenizing (const char *, TOK_STRUCT **);

