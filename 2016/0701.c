#include "stdio.h"
#include "string.h"

#define true 1
#define false 0

typedef int bool;

bool check_abba(char *str);

bool check_abba(char *str)
{
  int i;
  
  for (i=0; i<strlen(str)-3; i++)
  {
    if ((str[i] == str[i+3])
       &&(str[i+1] == str[i+2])
       &&(str[i] != str[i+1]))
    {
      return true;
    }
  }

  return false;
}

int main(int argc, char **argv)
{
  FILE *fp;
  char *ptr;
  bool found = false;
  bool hyper = false;
  bool abba = false;
  int sum = 0;
  char data[256];

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

  while(fscanf(fp, "%s ", data) != EOF)
  {
    printf("%s\n", data);

    ptr = strtok(data, "[]");
    while (ptr != NULL)
    {
      abba = check_abba(ptr);
      if (abba && hyper)
      {
        abba = false;
        hyper = false;
        found = false;
        break;
      }
      if (abba && !hyper)
      {
        found = true;
      }
      ptr = strtok(NULL, "[]");
      hyper = !hyper;
    }

    if (found == true)
    {
      sum++;
    }

    abba = false;
    hyper = false;
    found = false;
  }

  printf("sum is: %d\n", sum);
  fclose(fp);
  return 0;
}
