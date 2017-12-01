#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define DATA_LEN 4096

unsigned int c2ui(char input)
{
  unsigned int ret = 0;
  ret = input - '0';
  return ret;
}

int main(int argc, char **argv)
{
  FILE *fp;
  char data[DATA_LEN];
  char first = 0;
  char last = 0;
  unsigned int len = 0;
  unsigned int i = 0;
  unsigned int c = 0;
  unsigned int n = 0;
  unsigned int total = 0;

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

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("%s", data);
  }
  printf("\n");

  len = strlen(data) - 1;
  first = c2ui(data[0]);
  last = c2ui(data[len-1]);
  for (i=0; i<len-1; i++)
  {
    c = c2ui(data[i]);	
    n = c2ui(data[i+1]);
    if (c == n)
	{
	  total += c;
	}
  }

  if (last == first)
  {
    total += last;
  }
  
  printf("total %d\n", total);

  fclose(fp);
  return 0;
}
