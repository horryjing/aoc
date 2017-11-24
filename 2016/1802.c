#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 128
#define WIDTH 100
#define FLOORS 2

int main(int argc, char **argv)
{
  FILE *fp;
  char data[DATA_LEN];
  int floors = 0;
  char map[FLOORS][WIDTH] = {0};
  int i=0;
  int j=0;
  char a='.';
  char b='.';
  char c='.';
  int cnt=0;

  if (argc != 3)
  {
    printf("invalid input.\n");
    return 0;
  }

  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    printf("failed to input file.\n");
    return 0;
  }
  floors = atoi(argv[2]);

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("%s, %d\n", data, floors);
    
  }

  for (j=0; j<WIDTH; j++)
  {
    map[0][j] = data[j];
    if (map[0][j] == '.')
    {
      cnt++;
    }
  }
  floors--;

  while (floors>0)
  {
      for (j=0; j<WIDTH; j++)
      {
        if (j==0)
        {
          a='.';
          b=map[0][j];
          c=map[0][j+1];
        }
        else if (j==WIDTH-1)
        {
          a=map[0][j-1];
          b=map[0][j];
          c='.';
        }
        else
        {
          a=map[0][j-1];
          b=map[0][j];
          c=map[0][j+1];
        }
      
        if ((a=='^' && b=='^' && c=='.')
          ||(a=='.' && b=='^' && c=='^')
          ||(a=='^' && b=='.' && c=='.')
          ||(a=='.' && b=='.' && c=='^'))
        {
          map[1][j] = '^';
        }
        else
        {
          map[1][j] = '.';
        }
      }

      for (j=0; j<WIDTH; j++)
      {
        if (map[1][j] == '.')
        {
          cnt++;
        }
        map[0][j] = map[1][j];
      }
      floors--;
  }
  printf("cnt %d.\n", cnt);

  fclose(fp);
  return 0;
}
