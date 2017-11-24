#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 128
#define WIDTH 100
#define FLOORS 400000

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
    printf("%s\n", data);
    
  }

  for (j=0; j<WIDTH; j++)
  {
    map[0][j] = data[j];
  }

  for (i=1; i<FLOORS; i++)
  {
    for (j=0; j<WIDTH; j++)
    {
      if (j==0)
      {
        a='.';
        b=map[i-1][j];
        c=map[i-1][j+1];
      }
      else if (j==WIDTH-1)
      {
        a=map[i-1][j-1];
        b=map[i-1][j];
        c='.';
      }
      else
      {
        a=map[i-1][j-1];
        b=map[i-1][j];
        c=map[i-1][j+1];
      }
      
      if ((a=='^' && b=='^' && c=='.')
        ||(a=='.' && b=='^' && c=='^')
        ||(a=='^' && b=='.' && c=='.')
        ||(a=='.' && b=='.' && c=='^'))
      {
        map[i][j] = '^';
      }
      else
      {
        map[i][j] = '.';
      }
    }
  }

  for (i=0; i<FLOORS; i++)
  {
    printf("%02d: ", i);
    for (j=0; j<WIDTH; j++)
    {
      if (map[i][j] == '.')
      {
        cnt++;
      }
      printf("%c", map[i][j]);
    }
    printf("cnt %d\n", cnt);
  }
  printf("cnt %d.\n", cnt);

  fclose(fp);
  return 0;
}
