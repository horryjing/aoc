#include "stdio.h"

#define LEN 20
#define INVALID 0xFF
#define TOTAL 150

int list[LEN] = {43,3,4,10,21,44,4,6,47,41,34,17,17,44,36,31,46,9,27,38};
int comb[LEN] = {0};
int num = 0;

void init();
void combine(int n, int k);
void computer();

int main(int argc, char **argv)
{
  int i = 0;
  
  for (i=3; i<20; i++)
  {
    init();
    combine(LEN, i);
  }

  printf("comb %d\n", num);
  return 0;
}

void init()
{
  int i = 0;

  for (i=0; i<LEN; i++)
  {
    comb[i] = INVALID;
  }
}

void combine(int n, int k)
{
  int i = 0;
  
  for (i=n; i>=k; i--)
  {
    comb[k-1] = list[i-1];
    if (k > 1)
    {
      combine(i-1, k-1);
    }
    else
    {
      computer();
      //init();
    }
  }
}

void computer()
{
  int i = 0;
  int val = 0;

  for (i=0; i<LEN; i++)
  {
    if (comb[i] == INVALID)
    {
      break;
    }
    printf("%d ", comb[i]);
    val += comb[i];
  }
  printf("\n");

  if (val == TOTAL)
  {
    num++;
  }
  //printf("%d %d %d\n", comb[0], comb[1], comb[2]);
}
