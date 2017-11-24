#include "stdio.h"

int calc(int a, int b, int c, int d);

int main(int argc, char **argv)
{
  int a, b, c, d;
  int val = 0;
  int max = 0;

  for (a=1; a<97; a++)
  {
    for (b=1; b<97; b++)
    {
      for (c=1; c<97; c++)
      {
          d = 100-a-b-c;
          if (d<=0)
          {
            continue;
          }
          printf("%d\n", d);
          val = calc(a, b, c, d);
          if (val > max)
          {
            max = val;
          }
      }
    }
  }
  printf("max %d\n", max);

  return 0;
}

int calc(int a, int b, int c, int d)
{
  int val = 0;
  int e1 = 2*a;
  int e2 = 5*b-d;
  int e3 = 5*c-2*a-3*b;
  int e4 = 5*d-c;
  int e5 = 3*a+3*b+8*c+8*d;

  if ((e2 <= 0)
    ||(e3 <= 0)
    ||(e4 <= 0))
  {
    val = 0;
  }
  else if (e5 != 500)
  {
    val = 0;
  }
  else
  {
    val = e1*e2*e3*e4;
  }

  return val;
}
