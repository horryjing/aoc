#include "stdio.h"
#include "stdlib.h"

#define LEN 16
#define CENTER (LEN/2)

unsigned int array[LEN+1][LEN+1] = {0};

unsigned int sum(unsigned int i, unsigned int j)
{
  unsigned int ret = 0;

  ret = array[i+1][j] + array[i-1][j];
  ret += array[i][j+1] + array[i][j-1];
  ret += array[i+1][j+1] + array[i+1][j-1];
  ret += array[i-1][j+1] + array[i-1][j-1];

  return ret;
}

int main(int argc, char **argv)
{
  unsigned int input = 0;
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int num = 1;

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }

  input = atoi(argv[1]);
  printf("input %d\n", input);

  i = j = CENTER;
  array[i][j] = num;

  unsigned int layer = 4;
  unsigned int step = 1;
  while (layer--)
  {
    /*up*/
    unsigned int up = 0;
    up = step*2-1;
    while (up>0)
	{
	  j = j+1;
	  array[i][j] = sum(i,j);
	  if (array[i][j] > input)
	  {
	    printf("%d\n", array[i][j]);
		break;
	  }
	  up--;
	}
	/*left*/
	unsigned int left = 0;
	left = step*2-1;
	while (left>0)
	{
	  i = i-1;
	  array[i][j] = sum(i,j);;
	  if (array[i][j] > input)
	  {
	    printf("%d\n", array[i][j]);
		break;
	  }
	  left--;
	}

	/*down*/
    unsigned int down = 0;
	down = step*2;
	while (down>0)
	{
	  j = j-1;
	  array[i][j] = sum(i,j);
      if (array[i][j] > input)
	  {
	    printf("%d\n", array[i][j]);
		break;
	  }
	    down--;
	}

	/*right*/
    unsigned int right = 0;
	right = step*2;
    while (right>0)
	{
      i = i+1;
	  array[i][j] = sum(i,j);
	  if (array[i][j] > input)
	  {
	    printf("%d\n", array[i][j]);
		break;
	  }
	  right--;
    }

	step++;
  }

  printf("\n");
  for (i=0; i<LEN; i++)
  {
    for (j=0; j<LEN; j++)
	{
	  printf("%d\t", array[i][j]);
	}
	printf("\n");
  }
  printf("\n");

  return 0;
}

