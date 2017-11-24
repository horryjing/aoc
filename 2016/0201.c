#include "stdio.h"

typedef unsigned int u32;
typedef struct button_t{
    u32 num;
    u32 up;
    u32 down;
    u32 left;
    u32 right;
}button;

button pad[10];/*leave pad[0] unused*/

void dump_pad();
int init_pad();

void dump_pad()
{
  int i;

  for (i=1; i<10; i++)
  {
    printf("num %d, up %d, down %d, left %d, right %d.\n", 
            pad[i].num, pad[i].up, pad[i].down, pad[i].left, pad[i].right);
  }
}

int init_pad()
{
  int i;

  for (i=1; i<10; i++)
  {
    pad[i].num = i;
    pad[i].up = i;
    pad[i].down = i;
    pad[i].left = i;
    pad[i].right = i;

    /*up*/
    if ((i-3) > 0)
    {
      pad[i].up = i-3;
    }

    /*down*/
    if ((i+3) < 10)
    {
      pad[i].down = i+3;
    }

    /*left*/
    if ((i-1)%3 != 0)
    {
      pad[i].left = pad[i].num - 1;
    }

    /*right*/
    if ((i%3) != 0)
    {
      pad[i].right = pad[i].num + 1;
    }
  }

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
      printf("%d",btn->num);
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
