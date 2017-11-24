#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef long long u32;

u32 decompressed(char *data);

u32 decompressed(char *data)
{
  char *ptr = data;
  u32 len = 0;
  u32 repeat_len = 0;
  u32 repeat_time = 0;
  char *buf = NULL;

  while ((*ptr != '\r') && (*ptr != '\0'))
  {
    if (*ptr == '(')
    {
      ptr++;
      while (*ptr != 'x')
      {
        repeat_len *= 10;
        repeat_len += *ptr - '0';
        ptr++;
      }
      ptr++;
      while (*ptr != ')')
      {
        repeat_time *= 10;
        repeat_time += *ptr - '0';
        ptr++;
      }
      ptr++;

      buf  = (char *)malloc(repeat_len+1);
      memset(buf, 0, repeat_len+1);
      strncpy(buf, ptr, repeat_len);
      len += decompressed(buf) * repeat_time;

      ptr += repeat_len;

      repeat_len  = 0;
      repeat_time = 0;
      free(buf);
    }
    else
    {
      ptr++;
      len++;
    }
  }

  return len;
}

int main(int argc, char **argv)
{
  FILE *fp;
  char data[16384];
  u32 length = 0;

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }

  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    printf("failed to input file.\n");
    return 0;
  }

  fgets(data, 16384, fp);
  length = decompressed(data);
  printf("length: %ld\n", length);

  fclose(fp);
  return 0;
}
