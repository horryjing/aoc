#include "stdio.h"
#include "string.h"

#define DATA_LEN 1024

unsigned int sum_line(char *data)
{
  unsigned int num = 0;
  unsigned int largest = 0;
  unsigned int smallest = 99999;
  unsigned int sum = 0;
  unsigned int len = 0;
  unsigned int i = 0;

  len = strlen(data);
  for (i=0; i<len; i++)
  {
    if ((data[i] >= '0') && (data[i] <= '9'))
	{
	  num *= 10;
      num += data[i] - '0';
	}
	else
	{
	  if (num > largest)
	  {
	    largest = num;
	  }
	  if (num < smallest)
	  {
	    smallest = num;
	  }
	  num = 0;
	}
  }

  sum = largest - smallest;
  printf("l %d, s %d, sum %d\n", largest, smallest, sum);

  return sum;
}

int main(int argc, char **argv)
{
  FILE *fp;
  char data[DATA_LEN];
  unsigned int line = 0;
  unsigned int sum = 0;

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }

  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    printf("failed to input file.\n");
    return 0;
  }

  line = 0;
  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    line++;
    printf("line %d: %s", line, data);
	sum += sum_line(data);
  }

  printf("sum %d\n", sum);

  fclose(fp);
  return 0;
}
