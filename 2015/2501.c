#include "stdio.h"

typedef unsigned int u32;
typedef unsigned long long u64;

//u32 input_r = 5;
//u32 input_c = 4;
u32 input_r = 2981;
u32 input_c = 3075;

int main()
{
  u32 row = 0;
  u32 col = 0;
  u32 c = 0;
  u32 cnt = 0;

  u64 p = 0;
  u64 r = 0;

  while (1)
  {
    c++;
    for (col=1,row=c; (col<=c&&row>=1); col++,row--)
    {
      if (col==1 && row==1)
      {
        p = 20151125;
        r = p;
      }
      else
      {
        r = p*252533%33554393;
        p = r;
      }
      if (row==input_r && col==input_c)
      {
        printf("(%u,%u)->%llu\n", row, col, r);
        return 0;
      }
    }
  }

  return 0;
}
