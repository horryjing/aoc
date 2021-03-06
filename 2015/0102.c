#include "stdio.h"

#define DATA_LEN 8192 

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  char *p = NULL;
  int floor = 0;
  int position = 0;

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
  }

  position = 1;
  p = data;
  while (*p=='(' || *p==')')
  {
    if (*p == '(')
    {
      floor++;
    }
    else if (*p == ')')
    {
      floor--;
    }
    else
    {
      printf("error input\n");
      return 0;
    }

    if (floor == -1)
    {
      printf("position %d\n", position);
      break;
    }
    p++;
    position++;
  }

  fclose(fp);
  return 0;
}
