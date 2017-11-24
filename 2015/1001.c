#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char **argv)
{
  char *input = NULL;
  char *output = NULL;
  int times = 0;
  int i = 0;
  int j = 0;
  int cnt = 0;
  char c = 0;
  char *buffer = NULL;
  int size = 0;

  if (argc != 3)
  {
    printf("invalid input.\n");
    return 0;
  }
  times = atoi(argv[2]);
  size = strlen(argv[1])*times*100000;
  input = (char *)calloc(sizeof(char), size);
  output = (char *)calloc(sizeof(char), size);
  buffer = (char *)calloc(sizeof(char), 100);
  strcpy(input, argv[1]);
  printf("%s, %d\n", input, times);

  for (i=0; i<times; i++)
  {
    cnt = 0;
    c = 0;
    for (j=0; j<strlen(input); j++)
    {
      if (c==0) c=input[0];
      if (input[j] == c)
      {
        cnt++;
      }
      else
      {
        sprintf(buffer, "%d%c", cnt, c);
        strcat(output, buffer);
        c = input[j];
        cnt = 1;
      }
    }
    sprintf(buffer, "%d%c", cnt, c);
    strcat(output, buffer);
    printf("time: %d\n", i);
    //printf("%s\n", input);
    //printf("%s\n", output);
    memset(input, 0, sizeof(char)*size);
    strcpy(input, output);
    memset(output, 0, sizeof(char)*size);
    memset(buffer, 0, sizeof(char)*100);
    printf("\n");
  }

  printf("len %d\n", strlen(input));

  //free(input);
  //free(output);
  //free(buffer);
  return 0;
}
