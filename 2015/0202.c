#include "stdio.h"

#define DATA_LEN 64
#define MINI(x, y) (x<=y?x:y)

typedef unsigned int u32;

u32 calc_perimeter(u32 l, u32 w, u32 h);

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  u32 total = 0;
  u32 length = 0;
  u32 width = 0;
  u32 height = 0;

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
    sscanf(data, "%dx%dx%d", &length, &width, &height);
    total += calc_perimeter(length, width, height);  
  }

  printf("total %d\n", total);
  fclose(fp);
  return 0;
}

u32 calc_perimeter(u32 l, u32 w, u32 h)
{
  u32 square = 0;
  u32 a = 0;
  u32 b = 0;
  u32 c = 0;

  if (l <= w)
  {
    if (l <= h)
    {
      if (w <= h)
      {
        a = l;
        b = w;
        c = h;
      }
      else
      {
        a = l;
        b = h;
        c = w;
      }
    }
    else
    {
      a = h;
      b = l;
      c = w;
    }
  }
  else
  {
    if (h <= w)
    {
      a = h;
      b = w;
      c = l;
    }
    else
    {
      if (l <= h)
      {
        a = w;
        b = l;
        c = h;
      }
      else
      {
        a = w;
        b = h;
        c = l;
      }
    }
  }
  printf("a %d, b %d, c %d\n", a, b, c);

  square = a*b*c + 2*(a+b); 

  return square;
}
