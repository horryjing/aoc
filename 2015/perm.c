#include "stdio.h"

#define LEN 2

void swap(int * o, int i, int j)
{
  int tmp = o[i];
  o[i] = o[j];
  o[j] = tmp;
}

void cbk_print(int * subs)
{
  int i;

  printf("{");
  for(i = 0; i < LEN; i++)
  {
    printf("%d", subs[i]);
    (i == LEN - 1) ? printf("") : printf(", "); 
  }
  printf("}\n");
}

void perm(int list[], int s, int e) 
{     
  int i;
  
  if(s > e)     
  {
    cbk_print(list);
  }
  else    
  {         
    for(i = s; i <= e; i++)
    {             
      swap(list, s, i);             
      perm(list, s + 1, e);             
      swap(list, s, i);         
     }
  }                                             
}

int main()
{
  //int list[LEN] = {0,1,2,3,4,5,6,7};
  int list[LEN] = {0,1};
  perm(list, 0, 1);
  return 0;
}
