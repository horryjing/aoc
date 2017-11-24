#include "stdio.h"
#include "string.h"

#define DATA_LEN 64

char grid[1000][1000] = {0};

int turn_on(int sy, int sx, int dy, int dx);
int turn_off(int sy, int sx, int dy, int dx);
int toggle(int sy, int sx, int dy, int dx);

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  char on[] = "turn on %d,%d through %d,%d";
  char off[] = "turn off %d,%d through %d,%d";
  char tgl[] = "toggle %d,%d through %d,%d";
  int sy = 0;
  int sx = 0;
  int dy = 0;
  int dx = 0;
  int i = 0;
  int j = 0;
  int cnt = 0;

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
    if (sscanf(data, on, &sy, &sx, &dy, &dx) == 4)
    {
      turn_on(sy, sx, dy, dx);
    }
    else if (sscanf(data, off, &sy, &sx, &dy, &dx) == 4)
    {
      turn_off(sy, sx, dy, dx);
    }
    else if (sscanf(data, tgl, &sy, &sx, &dy, &dx) == 4)
    {
      toggle(sy, sx, dy, dx);
    }
    else
    {
      printf("error input\n");
      return 0;
    }
  }

  for (i=0; i<1000; i++)
  {
    for (j=0; j<1000; j++)
    {
      if (grid[i][j] == 1)
      {
        cnt++;
      }
    }
  }

  printf("cnt %d\n", cnt);

  fclose(fp);
  return 0;
}

int turn_on(int sy, int sx, int dy, int dx)
{
  int i = 0;
  int j = 0;

  for (i=sx; i<=dx; i++)
  {
    for (j=sy; j<=dy; j++)
    {
      grid[i][j] = 1;
    }
  }

  return 0;
}

int turn_off(int sy, int sx, int dy, int dx)
{
  int i = 0;
  int j = 0;

  for (i=sx; i<=dx; i++)
  {
    for (j=sy; j<=dy; j++)
    {
      grid[i][j] = 0;
    }
  }

  return 0;
}

int toggle(int sy, int sx, int dy, int dx)
{
  int i = 0;
  int j = 0;

  for (i=sx; i<=dx; i++)
  {
    for (j=sy; j<=dy; j++)
    {
      if (grid[i][j] == 0)
      {
        grid[i][j] = 1;
      }
      else
      {
        grid[i][j] = 0;
      }
    }
  }

  return 0;
}
