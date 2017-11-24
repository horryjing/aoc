#include "stdio.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define LEFT 0
#define RIGHT 1

int calc_pos(int dir, int mov, int *x, int *y, int *pos);

int main(int argc, char** argv)
{
  FILE *fp = NULL;
  char input = 0;
  int dir = LEFT;/*L=0, R=1*/
  int mov = 0;
  /*init pos, x=0, y=0, pos=North*/
  int x = 0;
  int y = 0;
  int pos = NORTH;
  
  /*check parameters*/
  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }

  /*read input file*/
  fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    printf("failed to open input file.\n");
    return 0;
  }

  /*parse input*/
  while ((input = fgetc(fp)) != EOF)
  {
    if (input == 'L')
    {
      dir = LEFT;
    }
    else if (input == 'R')
    {
      dir = RIGHT;
    }
    else if ((input >= '0') && (input <='9'))
    {
      mov *= 10;
      mov += input - '0';
    }
    else if ((input == ',') || (input == '\n'))
    {
      calc_pos(dir, mov, &x, &y, &pos);
      dir = 0;
      mov = 0;
    }
    else
    {
      continue;
    }
  }

  printf("distance is %d\n", abs(x)+abs(y));

  fclose(fp);
  return 0;
}

int calc_pos(int dir, int mov, int *x, int *y, int *pos)
{
  printf("dir %d, mov %d.\n", dir, mov);

  switch (*pos)
  {
    case NORTH:/*mov in x direction*/
      if (dir == LEFT)
      {
        mov = -mov;
        *pos = WEST;
      }
      else
      {
        *pos = EAST;
      }
      *x += mov;
      break;
    case EAST:/*mov in y direction*/
      if (dir == LEFT)
      {
        *pos = NORTH;
      }
      else
      {
        mov = -mov;
        *pos = SOUTH;
      }
      *y += mov;
      break;
    case SOUTH:/*mov in x direction*/
      if (dir == LEFT)
      {
        *pos = EAST;
      }
      else
      {
        mov = -mov;
        *pos = WEST;
      }
      *x += mov;
      break;
    case WEST:/*mov in y direction*/
      if (dir == LEFT)
      {
        mov = -mov;
        *pos = SOUTH;
      }
      else
      {
        *pos = NORTH;
      }
      *y += mov;
      break;
    default:
        printf("invalid position %d.\n", pos);
        return -1;
  }

  printf("x %d, y %d, pos %d.\n", *x, *y, *pos);
  return 0;

}
