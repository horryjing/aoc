#include "stdio.h"
#include "stdlib.h"

#define MAX_COL 100
#define MAX_ROW 100
#define FAV_NUM 1364
#define WALL 1
#define SPACE 2
#define INIT_DIST 254

typedef unsigned char u8;
typedef unsigned int u32;
typedef struct point_t{
  u8 r;
  u8 c;
  u8 d;
  struct point_t *next;
}point;

point *visited;
point *unvisited;
u8 map[MAX_ROW][MAX_COL] = {0};
u8 distance[MAX_ROW][MAX_COL] = {0};
u8 dcol=31;
u8 drow=39;
int size=0;

void draw_map();
void print_map();
//return 0:error, 1:wall 2:space
u8 space_wall(u8 x, u8 y);
u8 find_way();
point *create_point(u8 r, u8 c, u8 d);
point *find_min();
int is_visited(u8 r, u8 c);

int main(int argc, char **agrv)
{
  u8 dist = 0;

  draw_map();
  print_map();
  dist = find_way();
  //printf("dist %d\n", dist);
  printf("cnt %d\n", dist);

  return 0;
}

void draw_map()
{
  u8 i=0;
  u8 j=0;
  u8 ret=0;

  for (i=0; i<MAX_ROW; i++)
  {
    for (j=0; j<MAX_COL; j++)
    {
      if ((ret = space_wall(j, i)) == 0)
      {
        printf("error to calc space or wall.\n");
        return;
      }
      map[i][j] = ret;
    }
  }
}

void print_map()
{
  u8 i=0;
  u8 j=0;

  printf("   ");
  for (j=0; j<MAX_COL; j++)
  {
    printf("%02d ", j);
  }
  printf("\n");

  for (i=0; i<MAX_ROW; i++)
  {
    printf("%02d ", i);
    for (j=0; j<MAX_COL; j++)
    {
      if (map[i][j] == SPACE)
      {
        printf(".  ");
      }
      else if (map[i][j] == WALL)
      {
        printf("#  ");
      }
      else
      {
        printf("X  ");
      }
    }
    printf("\n");
  }
}


u8 space_wall(u8 x, u8 y)
{
  u32 val = 0;
  u8 cnt = 0;

  val = x*x + 3*x + 2*x*y + y + y*y;
  val += FAV_NUM;

  do
  {
    if (val & 0x1)
    {
      cnt++;
    }
    val = val >> 1;
  }while (val != 0);

  if (cnt % 2)
  {
    return WALL;  
  }
  else
  {
    return SPACE;
  }

  return 0;
}

u8 find_way()
{
  int i=0;
  int j=0;
  int r=0;
  int c=0;
  int d=0;
  point *cur = NULL;
  point *tmp = NULL;
  int cnt=0;

  for (i=0; i<MAX_ROW; i++)
  {
    for (j=0; j<MAX_COL; j++)
    {
      distance[i][j] = INIT_DIST;
    }
  }

  distance[1][1] = 0;
  unvisited = create_point(1, 1, 0);
  size++;
  //while (distance[drow][dcol] == INIT_DIST)
  while (unvisited != NULL)
  {
    cur = find_min();
    if (cur != NULL)
    {
      r = cur->r;
      c = cur->c;
      d = cur->d + 1;

      if ((r-1>=0) 
        && (d<distance[r-1][c]) 
        && (map[r-1][c] == SPACE))
      {
        distance[r-1][c] = d;
        if (is_visited(r-1, c) == 0)
        {
          tmp = create_point(r-1, c, d);
          tmp->next = unvisited;
          unvisited = tmp;
          size++;
          printf("%d, %d\n", r-1, c);
        }
      }
      if ((r+1<MAX_ROW)
        && (d<distance[r+1][c])
        && (map[r+1][c] == SPACE))
      {
        distance[r+1][c] = d;
        if (is_visited(r+1, c) == 0)
        {
          tmp = create_point(r+1, c, d);
          tmp->next = unvisited;
          unvisited = tmp;
          size++;
          printf("%d, %d\n", r+1, c);
        }
      }
      if ((c-1>=0)
        && (d<distance[r][c-1])
        && (map[r][c-1] == SPACE))
      {
        distance[r][c-1] = d;
        if (is_visited(r, c-1) == 0)
        {
          tmp = create_point(r, c-1, d);
          tmp->next = unvisited;
          unvisited = tmp;
          size++;
          printf("%d, %d\n", r, c-1);
        }
      }
      if ((c+1<MAX_COL)
        && (d<distance[r][c+1])
        && (map[r][c+1] == SPACE))
      {
        distance[r][c+1] = d;
        if (is_visited(r, c+1) == 0)
        {
          tmp = create_point(r, c+1, d);
          tmp->next = unvisited;
          unvisited = tmp;
          size++;
          printf("%d, %d\n", r, c+1);
        }
      }
      cur->next = visited;
      visited = cur;
      size--;
	  printf("curr size: %d\n", size);
    }
  }
  
  for (i=0; i<MAX_ROW; i++)
  {
    for (j=0; j<MAX_COL; j++)
    {
      if (distance[i][j] <= 50)
      {
        cnt++;        
      }
    }
  }

  //return distance[drow][dcol];
  return cnt;
}

point *create_point(u8 r, u8 c, u8 d)
{
  point *p=NULL;

  p = (point *)malloc(sizeof(point));
  p->r = r;
  p->c = c;
  p->d = d;
  p->next = NULL;
  
  return p;
}

point *find_min()
{
  point *min = unvisited;
  point *cur = unvisited;

  while (cur != NULL)
  {
    printf("%d\n", cur->d);
    if (cur->d < min->d)
    {
      min = cur;
    }
    cur = cur->next;
  }

  cur = unvisited;
  while (cur != NULL)
  {
    if (cur->next == min)
    {
      break;
    }
    cur = cur->next;
  }

  if (cur == NULL)
  {
    unvisited = min->next;
  }
  else
  {
    cur->next = min->next;
  }

  return min;
}

int is_visited(u8 r, u8 c)
{
  point *p = visited;

  while (p != NULL)
  {
    if ((r == p->r) && (c == p->c))
    {
      break;
    }
    p = p->next;
  }

  if (p == NULL)
  {
    return 0;
  }

  return 1;
}

