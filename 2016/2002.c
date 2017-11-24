#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 64
#define NUM 4294967296

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  unsigned long int i = 0;
  unsigned long int start = 0;
  unsigned long int end = 0;
  unsigned long int cnt = 0;
  char *ip = NULL;

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

  ip = (char *)malloc(NUM*sizeof(char));
  for (i=0; i<NUM; i++)
  {
    ip[i] = 1;
    if (i%100000000==0)
    {
      printf("%lu\n", i);
    }
  }

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    sscanf(data, "%lu-%lu", &start, &end);
    printf("%lu-%lu\n", start, end);
    
    for (i=start; i<=end; i++)
    {
      ip[i] = 0;
    }
  }

  for (i=0; i<NUM; i++)
  {
    if (ip[i] == 1)
    {
      cnt++;
    }
  }

  printf("cnt %lu.\n", cnt);

  free(ip);
  fclose(fp);
  return 0;
}
