#include "stdio.h"
#include "stdlib.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define LEFT 0
#define RIGHT 1

typedef struct point_t{
  int x;
  int y;
  struct point_t * next;
}point;

point *head = NULL;

int ops_point(int last_x, int last_y, int x, int y, int *ret_x, int *ret_y);
int add_point(int x, int y);
int release_list();
int find_point(int x, int y);
int calc_pos(int dir, int mov, int *x, int *y, int *pos);
void dump_list();

void dump_list()
{
  point *tmp = NULL;

  tmp = head;
  while (tmp != NULL)
  {
    printf("(%d,%d)->", tmp->x, tmp->y);
    tmp = tmp->next;
  }
}

int ops_point(int last_x, int last_y, int x, int y, int *ret_x, int *ret_y)
{
  int i = 0;
  int dir = 0;
  int step = 0;

  *ret_x = 0;
  *ret_y = 0;

  printf("last_x %d, last_y %d, x %d, y %d\n", last_x, last_y, x, y);
  if ((last_x != x) && (last_y == y))
  {
    if (last_x < x)
    {
      dir = 1;
      step = x - last_x;
    }
    else
    {
      dir = -1;
      step = last_x - x;
    }
    for (i=1; i<=step; i++)
    {
      if (find_point((last_x+i*dir), y) == 1)
      {
        *ret_x = last_x+i*dir;
        *ret_y = y;
        return 1;
      }
      add_point(last_x+i*dir, y);
    }
  }
  else if ((last_x == x) && (last_y != y))
  {
    if (last_y < y)
    {
      dir = 1;
      step = y - last_y;
    }
    else
    {
      dir = -1;
      step = last_y - y;
    }
    for (i=1; i<=step; i++)
    {
      if (find_point(x, (last_y+i*dir)) == 1)
      {
        *ret_x = x;
        *ret_y = last_y+i*dir;
        return 1;
      }
      add_point(x, last_y+i*dir);
    }
  }
  else
  {
    dump_list();
    printf("invalid input.\n");
    return -1;
  }

  return 0;
}

int add_point(int x, int y)
{
  point *new = NULL;
  point *tmp = NULL;

  new = (point *)malloc(sizeof(point));
  if (new == NULL)
  {
    printf("failed to malloc mem.\n");
    return -1;
  }
  new->x = x;
  new->y = y;
  new->next = NULL;

  if (head == NULL)
  {
    head = new;
    return 0;
  }

  tmp = head;
  while (tmp->next != NULL)
  {
    tmp = tmp->next;
  }
  tmp->next = new;
  return 0;
}

int release_list()
{
  point *tmp = NULL;

  tmp = head;
  while (tmp != NULL)
  {
    head = tmp->next;
    free(tmp);
    tmp = head;
  }

  head = NULL;

  return 0;
}

/*return 1 if found it point, else return 0*/
int find_point(int x, int y)
{
  point *tmp = NULL;

  tmp = head;
  while (tmp != NULL)
  {
    if ((tmp->x == x) && (tmp->y == y))
    {
      break;
    }
    tmp = tmp->next;
  }

  if (tmp != NULL)
  {
    return 1; /*found the point*/
  }

  return 0;
}

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

  int last_x = 0;
  int last_y = 0;
  int ret_x = 0;
  int ret_y = 0;

  add_point(x, y);
  
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
      last_x = x;
      last_y = y;
      calc_pos(dir, mov, &x, &y, &pos);
      if (ops_point(last_x, last_y, x, y, &ret_x, &ret_y) == 1)
      {
        printf("distance is %d\n", abs(ret_x)+abs(ret_y));
        break;
      }
      dir = 0;
      mov = 0;
    }
    else
    {
      continue;
    }
  }

  dump_list();
  release_list();
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
