#include "stdio.h"

typedef unsigned int u32;

int main(int argc, char **argv)
{
  FILE *fp;
  char *input;
  u32 len1, len2, len3;
  u32 num = 0;

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

  while(fscanf(fp, "%d %d %d ", &len1, &len2, &len3) != EOF)
  {
    if (len1+len2>len3 && len1+len3>len2 && len2+len3>len1)
    {
      num++;
    }
  }

  printf("number of triangle is %d.\n", num);

  fclose(fp);
  return 0;
}
