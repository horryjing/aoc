#include "stdio.h"
#include "string.h"

#define DATA_LEN 32

int rule1(char *str);
int rule2(char *str);

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
    if (rule1(data) && rule2(data))
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

int rule1(char *str)
{
  int i = 0;
  int j = 0;
  char *p = str;

  for (i=0; i<strlen(str)-2; i++)
  {
    for (j=i+2; j<strlen(str); j++)
    {
      if ((p[i]==p[j]) && (p[i+1]==p[j+1]))
      {
        return 1;
      }
    }
  }

  return 0;
}

int rule2(char *str)
{
  int i = 0;
  char *p = str;

  for (i=0; i<strlen(str)-2; i++)
  {
    if (p[i] == p[i+2])
    {
      return 1;
    }
  }

  return 0;
}
