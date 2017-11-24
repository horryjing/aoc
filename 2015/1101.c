#include "stdio.h"
#include "string.h"

#define LEN 8

int gen(char input[]);
int rule1(char input[]);
int rule2(char input[]);
int rule3(char input[]);

int main(int argc, char **argv)
{
  char input[LEN] = {0};
  int i = 0;

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }
  for (i=0; i<LEN; i++)
  {
    input[i] = argv[1][i];
    printf("%c", input[i]);
  }
  printf("\n");

  while ((rule1(input) == 0)
    || (rule2(input) == 0)
    || (rule3(input) == 0))
  {
    gen(input);
  }

  for (i=0; i<LEN; i++)
  {
    printf("%c", input[i]);
  }
  printf("\n");

  return 0;
}

int gen(char input[])
{
  int i = 0;
  int plus = 0;

  for (i=LEN-1; i>=0; i--)
  {
    if ((input[i]+1)>'z')
    {
      input[i] = 'a';
      plus++;
    }
    else
    {
      input[i]++;
      plus = 0;
    }
    if (plus == 0)
    {
      break;
    }
  }

  return 1;
}

int rule1(char input[])
{
  int i = 0;

  for (i=0; i<LEN-2; i++)
  {
    if ((input[i]+1 == input[i+1])
      &&(input[i]+2 == input[i+2]))
    {
      return 1;
    }
  }
  return 0;
}

int rule2(char input[])
{
  int i = 0;
  char v[3];
  int j = 0;

  v[0] = 'i';
  v[1] = 'o';
  v[2] = 'l';

  for (i=0; i<LEN; i++)
  {
    for (j=0; j<3; j++)
    {
      if (input[i] == v[j])
      {
        return 0;
      }
    }
  }
  return 1;
}

int rule3(char input[])
{
  int i = 0;
  int j = 0;

  for (i=0; i<LEN-1; i++)
  {
    if (input[i] == input[i+1])
    {
      j = i + 2;
      break;
    }
  }
  for (; j<LEN-1; j++)
  {
    if ((input[j] == input[j+1])
      && (input[i] !=  input[j]))
    {
      return 1;
    }
  }

  return 0;
}
