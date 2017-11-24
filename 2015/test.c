#include "stdio.h"

void comb(int n, int m);
void post();
void print();

int l[] = {1,2,3,4,5,7,8,9,10,11};
int l1[10] = {0};
int weight = 0;
long long min = 0xfffffffffffffff;

int main()
{
  int i = 0;

  for (i=0; i<10; i++)
  {
    weight += l[i];
  }
  weight /= 3;
  printf("weight: %d\n", weight);

  for (i=1; i<=10; i++)
  {
    comb(10, i);
    //comb(10, 1);
  }

  printf("min %llu\n", min);
  return 0;
}

void comb(int n, int m)
{
  int i = 0;
  int k = 0;

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
      //print();
    }
  }
}

void print()
{
  int i = 0;
  for (i=0; i<10; i++)
  {
    if (l1[i] == 0)
    {
      continue;
    }
    printf("%d ", l1[i]);
  }
  printf("\n");
}

void post()
{
  int i = 0;
  int w = 0;
  long long q = 1;

  for (i=0; i<10; i++)
  {
    w += l1[i];
  }
  if (w != weight)
  {
    return;
  }
  for (i=0; i<10; i++)
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
