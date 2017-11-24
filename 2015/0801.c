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
  
  if ((p[0] != '\"') || (p[len-1] != '\"'))
  {
    printf("error 1: %s\n", data);
    return 0;
  }

  for (i=1; i<=len-2; i++)//exclude the first and last \"
  {
    if (p[i] == '\\')
    {
      if (p[i+1] == '\\')
      {
        cnt++;
        i += 1;
      }
      else if (p[i+1] == '\"')
      {
        cnt++;
        i += 1;
      }
      else if (p[i+1] == 'x')
      {
        if ((p[i+2] >= '0' && p[i+2] <= 'f')
          ||(p[i+3] >= '0' && p[i+3] <= 'f'))
        {
          cnt++;
          i += 3;
        }
        else
        {
          printf("error 3: %s\n", data);
          return 0;
        }
      }
      else
      {
        printf("error 2: %s\n", data);
        return 0;
      }
    }
    else
    {
      cnt++;
    }
  }

  return cnt;
}
