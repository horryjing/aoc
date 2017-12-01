#include "stdio.h"

#define DATA_LEN 64

int main(int argc, char **argv)
{
  FILE *fp;
  char data[DATA_LEN];

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

  fclose(fp);
  return 0;
}
