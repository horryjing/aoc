#include "stdio.h"

#define DATA_LEN 30000

int is_digital(char c);
int sum(char *data);

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  int cnt = 0;
  char *p = data;
  int nagtive = 0;
  int num = 0;

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

  while (*p != '\n')
  {
    if ((*p == '-') && is_digital(*(p+1)))
    {
      nagtive = 1;
    }
    else if (is_digital(*p))
    {
      num *= 10;
      num += *p - '0';
    }
    else
    {
      if (nagtive == 1)
      {
        num = -num;
      }
      cnt += num;
      num = 0;
      nagtive = 0;
    }
    p++;
  }
  printf("cnt %d\n", cnt);

  fclose(fp);
  return 0;
}

int is_digital(char c)
{
  if (c>='0' && c<='9')
  {
    return 1;
  }
  return 0;
}
