#include "stdio.h"

typedef unsigned int u32;

u32 decompressed(char *data);

u32 decompressed(char *data)
{
  char *ptr = data;
  u32 len = 0;
  u32 repeat_len = 0;
  u32 repeat_time = 0;

  while (*ptr != '\r')
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
      ptr += repeat_len;
      len += repeat_len * repeat_time;
      repeat_len  = 0;
      repeat_time = 0;
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
  u32 length;

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
  printf("length: %d\n", length);

  fclose(fp);
  return 0;
}
