#include "include/crypt.h"


uint64_t decrypt(char * out, char *in, uint64_t n)
{
  uint64_t v3; 
  uint64_t result;
  char v5; 
  uint64_t v6;

  v3 = n - 1;
  result = (uint64_t)out;
  if ( v3 )
  {
    v5 = *in;
    if ( *in == 0x21 )
    {
      v3 = 0;
    }
    else
    {
      v6 = 0;
      while ( 1 )
      {
        *(char *)(out + v6++) = v5 - 0x21;
        if ( v6 == v3 )
          break;
        v5 = in[v6];
        if ( v5 == 0x21 )
        {
          *(char *)(out + v6) = 0;
          return result;
        }
      }
    }
  }
  *(char *)(out + v3) = 0;
  return result;
}

int md5(char *str, char *out) {
  char *format = "echo -n %s | md5sum";
  char command[SMALL_BUFFER_SIZE];
  sprintf(command, format, str);
  FILE *cmd = popen(command, "r");
  if(cmd == NULL) return ERROR;
  fscanf(cmd, "%s", out);
  fclose(cmd);
  return SUCCESS;
}