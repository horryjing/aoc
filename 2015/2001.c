#include "stdio.h"


int main(int argc, char **argv)
{
  int input = 0;
  int i = 0;
  int sum = 0;
  int l = 0;
  int v = 0;

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }
  input = atoi(argv[1]);
  printf("%d\n", input);

  input /= 10;
  v = 770000; 
  i = v;
  while (sum < input)
  {
    sum = 0;
    i = v;
    for (l=1; l<i; l++)
    {
      if (v%l == 0)
      {
        sum += l;
        sum += v/l;
        i = v/l;
        //printf("%d + %d + ", l, v/l);
      }
    }
    v++;
    if (v%1000==0)
    {
      printf("%d,", v);
    }
    if (v==input)
    {
      break;
    }
  }

  printf("*****%d\n", v-1);

  return 0;
}
