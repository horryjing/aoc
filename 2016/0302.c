#include "stdio.h"

typedef unsigned int u32;

int main(int argc, char **argv)
{
  FILE *fp;
  char *input;
  u32 len11, len12, len13;
  u32 len21, len22, len23;
  u32 len31, len32, len33;
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

  while((fscanf(fp, "%d %d %d ", &len11, &len21, &len31) != EOF)
      &&(fscanf(fp, "%d %d %d ", &len12, &len22, &len32) != EOF)
      &&(fscanf(fp, "%d %d %d ", &len13, &len23, &len33) != EOF))
  {
    if (len11+len12>len13 && len11+len13>len12 && len12+len13>len11)
    {
      num++;
    }
    if (len21+len22>len23 && len21+len23>len22 && len22+len23>len21)
    {
      num++;
    }
    if (len31+len32>len33 && len31+len33>len32 && len32+len33>len31)
    {
      num++;
    }
  }

  printf("number of triangle is %d.\n", num);

  fclose(fp);
  return 0;
}
