#include "stdio.h"

#define A 10
#define B 11
#define C 12
#define D 13

typedef unsigned int u32;
typedef struct button_t{
    u32 num;
    u32 up;
    u32 down;
    u32 left;
    u32 right;
}button;

button pad[14];/*leave pad[0] unused*/

void dump_pad();
int init_pad();

void dump_pad()
{
  int i;

  for (i=1; i<14; i++)
  {
    printf("num %d, up %d, down %d, left %d, right %d.\n", 
            pad[i].num, pad[i].up, pad[i].down, pad[i].left, pad[i].right);
  }
}

int init_pad()
{
  int i;
  for (i=1; i<14; i++)
  {
    pad[i].num = i;
  }

  pad[1].up = 1;
  pad[1].down = 3;
  pad[1].left = 1;
  pad[1].right = 1;

  pad[2].up = 2;
  pad[2].down = 6;
  pad[2].left = 2;
  pad[2].right = 3;

  pad[3].up = 1;
  pad[3].down = 7;
  pad[3].left = 2;
  pad[3].right = 4;

  pad[4].up = 4;
  pad[4].down = 8;
  pad[4].left = 3;
  pad[4].right = 4;

  pad[5].up = 5;
  pad[5].down = 5;
  pad[5].left = 5;
  pad[5].right = 6;

  pad[6].up = 2;
  pad[6].down = A;
  pad[6].left = 5;
  pad[6].right = 7;

  pad[7].up = 3;
  pad[7].down = B;
  pad[7].left = 6;
  pad[7].right = 8;

  pad[8].up = 4;
  pad[8].down = C;
  pad[8].left = 7;
  pad[8].right = 9;

  pad[9].up = 9;
  pad[9].down = 9;
  pad[9].left = 8;
  pad[9].right = 9;

  pad[A].up = 6;
  pad[A].down = A;
  pad[A].left = A;
  pad[A].right = B;

  pad[B].up = 7;
  pad[B].down = D;
  pad[B].left = A;
  pad[B].right = C;

  pad[C].up = 8;
  pad[C].down = C;
  pad[C].left = B;
  pad[C].right = C;

  pad[D].up = B;
  pad[D].down = D;
  pad[D].left = D;
  pad[D].right = D;

  return 0;
}

int main(int argc, char **argv)
{
  FILE *fp;
  char input;
  button *btn; 

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }

  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    printf("failed to open input file.\n");
    return 0;
  }

  init_pad();
  dump_pad();
  btn = &pad[5];

  while ((input = fgetc(fp)) != EOF)
  {
    if (input == '\n')
    {
      /*finished one line*/
      if ((btn->num >= 10) && (btn->num <= 13))
      {
        printf("%c", btn->num+55);
      }
      else
      {
        printf("%d",btn->num);
      }
      continue;
    }

    /*parse current line*/
    if (input == 'U')
    {
      btn = &pad[btn->up];
    }
    else if (input == 'D')
    {
      btn = &pad[btn->down];
    }
    else if (input == 'L')
    {
      btn = &pad[btn->left];
    }
    else if (input == 'R')
    {
      btn = &pad[btn->right];
    }
    else
    {
      printf("invalid mov.\n");
      return 0;
    }
  }

  printf("\n");
  close(fp);
  return 0;
}
