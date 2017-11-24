#include "stdio.h"
#include "string.h"

#define DATA_LEN 64

typedef unsigned int u32;

u32 char_cnt(char *data);

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  u32 acnt = 0;
  u32 ccnt = 0;

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

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("%s", data);
    acnt += strlen(data)-1;//minus '\n'
    ccnt += char_cnt(data);
    printf("%d, %d\n", strlen(data)-1, acnt);
    printf("%d, %d\n", char_cnt(data), ccnt);
  }

  fclose(fp);
  return 0;
}

u32 char_cnt(char *data)
{
  u32 cnt = 0;
  u32 i = 0;
  u32 len = strlen(data)-1;
  char *p = data;
  
  for (i=0; i<len; i++)
  {
    if ((p[i] == '\"')
      ||(p[i] == '\\'))
    {
      cnt += 2;
    }
    else
    {
      cnt++;
    }
  }

  cnt += 2;

  return cnt;
}
