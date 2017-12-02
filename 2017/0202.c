#include "stdio.h"
#include "string.h"

#define DATA_LEN 1024
#define ARRAY_LEN 16

unsigned int sum_line(char *data)
{
  unsigned int num = 0;
  unsigned int array[ARRAY_LEN] = {0};
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int len = 0;
  unsigned int sum = 0;
  unsigned int l = 0;
  unsigned int s = 0;

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
	  array[j] = num;
	  j++;
	  num = 0;
	}
  }
  for (i=0; i<ARRAY_LEN; i++)
  {
    printf("%d ", array[i]);
  }
  printf("\n");

  for (i=0; i<ARRAY_LEN; i++)
  {
    for (j=i+1; j<ARRAY_LEN; j++)
	{
	  if (array[i] > array[j])
	  {
        l = array[i];
		s = array[j];
	  }
	  else
	  {
	    l = array[j];
		s = array[i];
	  }
	  if ((l%s == 0)&&(l/s > sum))
	  {
	    sum = l/s;
	  }
	}
  }

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
