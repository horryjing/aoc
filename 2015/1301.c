#include "stdio.h"

#define LEN 8

char relate[LEN][LEN] = 
{
        //A0      B1     C2      D3      E4      F5      G6      M7
/*0*/   {0,      -57,    -62,    -75,    71,     -22,    -23,    -76},
/*1*/   {-14,     0,     48,     89,     86,     -2,     27,     19},
/*2*/   {37,     45,     0,      24,     5,      -68,    -25,    30},
/*3*/   {-51,    34,     99,     0,      91,     -38,    60,     -63},
/*4*/   {23,     -69,    -33,    -47,    0,      75,     82,     13},
/*5*/   {77,     27,     -87,    74,     -41,    0,      -99,    26},
/*6*/   {-63,    -51,    -60,    30,     -100,   -63,    0,      57},
/*7*/   {-71,    -28,    -10,    44,     22,     79,     -16,    0}
};

int list[LEN] = {0,1,2,3,4,5,6,7};
int max = 0;

int computer(int list[]);
void swap(int list[], int i, int j);
void perm(int list[], int s, int e);

int main(int argc, char **argv)
{
  perm(list, 0, LEN-1);
  printf("max %d\n", max);
  return 0;
}

int computer(int list[])
{
  int i = 0;
  int h = 0;

  for (i=0; i<LEN; i++)
  {
    printf("%d ", list[i]);
  }
  printf("\n");

  for (i=0; i<LEN; i++)
  {
    if (i==LEN-1)
    {
      h += relate[list[i]][list[0]];
      h += relate[list[0]][list[i]];
      printf("relate %d->%d: %d\n", list[i], list[0], relate[list[i]][list[0]]);
      printf("relate %d->%d: %d\n", list[0], list[i], relate[list[0]][list[i]]);
      continue;
    }
    h += relate[list[i]][list[i+1]];
    h += relate[list[i+1]][list[i]];
    printf("relate %d->%d: %d\n", list[i], list[i+1], relate[list[i]][list[i+1]]);
    printf("relate %d->%d: %d\n", list[i+1], list[i], relate[list[i+1]][list[i]]);
  }

  printf("%d\n", h);
  if (h > max) max = h;

  return 0;
}

void swap(int list[], int i, int j)
{
  int tmp = list[i];
  list[i] = list[j];
  list[j] = tmp;
}

void perm(int list[], int s, int e)
{
  int i = 0;

  if (s>e)
  {
    computer(list);
  }
  else
  {
    for (i=s; i<=e; i++)
    {
      swap(list, s, i);
      perm(list, s+1, e);
      swap(list, s, i);
    }
  }
}
