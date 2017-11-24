#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv)
{
  int num = 0;
  int *elves = NULL;
  int i = 0;
  int cur = 0;
  int left = 0;

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }
  num = atoi(argv[1]);
  printf("num %d\n", num);

  elves = (int *)malloc(num*sizeof(int));

  for (i=0; i<num; i++)
  {
    elves[i] = 1;
  }

  while (1)
  {
    if (elves[cur] != 0)
    {
      left = cur + 1;
      left %= num;
      while (elves[left] == 0)
      {
        left++;
        left %= num;
      }
      elves[cur] += elves[left];
      if (elves[cur] == num)
      {
        break;
      }
      elves[left] = 0;
    }
    cur++;
    cur %= num;
  }

  free(elves);
  printf("num %d.\n", cur+1);
  return 0;
}
