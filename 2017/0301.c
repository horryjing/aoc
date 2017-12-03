#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv)
{
  unsigned int input = 0;
  unsigned int step = 0;
  unsigned int layer = 0;
  unsigned int num = 0;

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }

  input = atoi(argv[1]);
  printf("input %d\n", input);

  while (1)
  {
    step = layer*2+1;
    num = step*step;
	if (num >= input)
	{
	  break;
	}
	layer++;
  }

  unsigned int one_s = 0;
  unsigned int one_e = 0;
  unsigned int two_s = 0;
  unsigned int two_e = 0;
  unsigned int three_s = 0;
  unsigned int three_e = 0;
  unsigned int four_s = 0;
  unsigned int four_e = 0;
  four_e = num;
  four_s = four_e - step + 1;
  three_e = four_s;
  three_s = three_e - step + 1;
  two_e = three_s;
  two_s = two_e - step + 1;
  one_e = two_s;
  one_s = one_e - step + 1;

  unsigned int range_s = 0;
  unsigned int range_e = 0;
  if ((input >= four_s) && (input <= four_e))
  {
    range_s = four_s;
    range_e = four_e;
  }
  else if ((input >= three_s) && (input <= three_e))
  {
    range_s = three_s;
	range_e = three_e;
  }
  else if ((input >= two_s) && (input <= two_e))
  {
    range_s = two_s;
	range_e = two_e;
  }
  else if((input >= one_s) && (input <= one_e))
  {
    range_s = one_s;
	range_e = one_e;
  }
  else
  {
    printf("error\n");
	return 0;
  }

  unsigned int center = 0;
  center = (range_e - range_s) / 2 + range_s;

  unsigned int distance = 0;
  distance = (input > center) ? input-center: center-input;
  distance += layer;

  printf("distance %d\n", distance);
  return 0;
}
