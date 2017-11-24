#include "stdio.h"
#include "string.h"

#define DATA_LEN 128
#define LEN 100
//#define LEN 6
#define ON '#'
#define OFF '.'

char grid[LEN][LEN] = {0};
char backup[LEN][LEN] = {0};
char neig[8][2] = 
{
  {-1,-1},  {-1,0},     {-1,1},
  {0,-1},               {0,1},
  {1,-1},   {1,0},      {1,1}
};

int neigh_ons(int x, int y);
int lights_on();
int show(char list[LEN][LEN]);
int sync();

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  int i = 0;
  int j = 0;
  int t = 0;
  int times = 0;
  int num = 0;

  if (argc != 3)
  {
    printf("invalid input.\n");
    return 0;
  }

  times = atoi(argv[2]);
  printf("times %d\n", times);

  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    printf("failed to input file.\n");
    return 0;
  }

  i = 0;
  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    for (j=0; j<LEN; j++)
    {
      grid[i][j] = data[j];
    }
    i++;
  }
  sync();
  //show(backup);

  for (t=0; t<times; t++)
  {
    for (i=0; i<LEN; i++)
    {
      for (j=0; j<LEN; j++)
      {
        num = neigh_ons(i, j);
        if (grid[i][j] == ON)
        {
          if ((num!=2) && (num!=3))
          {
            grid[i][j] = OFF;
          }
        }
        else
        {
          if (num == 3)
          {
            grid[i][j] = ON;
          }
        }
      }
    }
    sync();
    //show(grid);
  }
  show(grid);
  printf("on: %d\n", lights_on());

  fclose(fp);
  return 0;
}

int neigh_ons(int x, int y)
{
  int i = 0;
  int cnt = 0;
  int nx = x;
  int ny = y;

  for (i=0; i<8; i++)
  {
    if ((x+neig[i][0])<0 || (x+neig[i][0])>LEN-1)
    {
      continue;
    }
    if ((y+neig[i][1]<0) || (y+neig[i][1]>LEN-1))
    {
      continue;
    }
    nx = x+neig[i][0];
    ny = y+neig[i][1];
    if (backup[nx][ny] == ON)
    {
      cnt++;
    }
  }

  return cnt;
}

int lights_on()
{
  int i=0;
  int j=0;
  int cnt=0;

  for (i=0; i<LEN; i++)
  {
    for (j=0; j<LEN; j++)
    {
      if (grid[i][j] == ON)
      {
        cnt++;
      }
    }
  }
  return cnt;
}

int show(char list[LEN][LEN])
{
  int i=0;
  int j=0;

  for (i=0; i<LEN; i++)
  {
    for (j=0; j<LEN; j++)
    {
      printf("%c", list[i][j]);
    }
    printf("\n");
  }

  printf("**********finish************\n");
  return 0;
}

int sync()
{
  int i=0;
  int j=0;

  for (i=0; i<LEN; i++)
  {
    for (j=0; j<LEN; j++)
    {
      backup[i][j] = grid[i][j];
    }
  }

  return 0;
}
