#include "stdio.h"
#include "string.h"

#define DATA_LEN 32

int vowels(char *str);
int repeat(char *str);
int exclude(char *str);

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  int cnt = 0;
  int i = 0;

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

  i = 1;
  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    //printf("%d: %s", i, data);
    if (vowels(data) && repeat(data) && exclude(data))
    {
      cnt++;
      printf("%s\n", data);
    }
    i++;
  }

  printf("%d\n", cnt);

  fclose(fp);
  return 0;
}

int vowels(char *str)
{
  char dir[5] = "aeiou";
  int num = 0;
  char *p = str;
  int i = 0;

  while (*p != '\r')
  {
    for (i=0; i<5; i++)
    {
      if (*p == dir[i])
      {
        num++;
        if (num >= 3)
        {
          return 1;
        }
      }
    }
    p++;
  }

  return 0;
}

int repeat(char *str)
{
  int i = 0;
  char *p = str;

  for (i=0; i<strlen(str)-1; i++)
  {
    if (p[i] == p[i+1])
    {
      return 1;
    }
  }

  return 0;
}

int exclude(char *str)
{
  char ex[4][3] = {"ab", "cd", "pq", "xy"};
  char *p = str;
  int i = 0;

  for (i=0; i<4; i++)
  {
    p = str;
    p = strstr(p, ex[i]);
    if (p != NULL)
    {
      return 0;
    }
  }

  return 1;
}
