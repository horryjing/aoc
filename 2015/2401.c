#include "stdio.h"

void comb(int n, int m);
void post();

int l[] = {1,2,3,5,7,13,17,19,23,29,31,37,41,43,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113};
int l1[29] = {0};
int weight = 0;
long long min = 0xfffffffffffffff;

int main()
{
  int i = 0;

  for (i=0; i<29; i++)
  {
    weight += l[i];
  }
  weight /= 3;
  printf("weight: %d\n", weight);

  //for (i=1; i<29; i++)
  {
    //comb(29, i);
    comb(29, 6);
  }

  printf("min %llu\n", min);
  return 0;
}

void comb(int n, int m)
{
  int i = 0;

  for (i=n; i>=m; i--)
  {
    l1[m-1] = l[i-1];
    if (m > 1)
    {
      comb(i-1, m-1);
    }
    else
    {
      post();
    }
  }
}

void post()
{
  int i = 0;
  int w = 0;
  long long q = 1;

  for (i=0; i<29; i++)
  {
    w += l1[i];
  }
  if (w != weight)
  {
    return;
  }
  
  for (i=0; i<29; i++)
  {
    if (l1[i] != 0)
    {
      q *= l1[i];
      printf("%d ", l1[i]);
    }
  }
  printf("\t\t\t\%d %015llu", w, q);
  printf("\n");

  if (q<min)
  {
    min = q;
  }
}
