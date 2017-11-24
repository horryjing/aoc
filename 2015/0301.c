#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 8194
#define COLS 8192
#define ROWS 8192

char *grid = NULL;

int set_value(int r, int c, int value);
int get_value(int r, int c);

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  int r = 0;
  int c = 0;
  char *p = NULL;
  int cnt = 0;
  int value = 0;

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

  grid = calloc(sizeof(char), COLS*ROWS);

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("%s\n", data);
  }

  set_value(r, c, 1);
  p = data;
  while (*p != '\n')
  {
    if (*p == '^')
    {
      r--;
    }
    else if (*p == 'v')
    {
      r++;
    }
    else if (*p == '<')
    {
      c--;
    }
    else if (*p == '>')
    {
      c++;
    }
    
    value = get_value(r, c);
    value++;
    set_value(r, c, value);

    p++;
  }

  for (r=-4095; r<4096; r++)
  {
    for (c=-4095; c<4096; c++)
    {
      value = get_value(r, c);
      if (value > 0)
      {
        cnt++;
      }
    }
  }

  printf("cnt %d\n", cnt);

  free(grid);
  fclose(fp);
  return 0;
}

int set_value(int r, int c, int value)
{
  char *p = grid;

  r += 4095;
  c += 4095;
  p += r*COLS + c;
  *p = value;

  return 0;
}

int get_value(int r, int c)
{
  char *p = grid;

  r += 4095;
  c += 4095;
  p += r*COLS + c;

  return *p;
}
