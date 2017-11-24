#include "stdio.h"
#include "string.h"

void get_rect_info(char *data, int *x, int *y);
void get_rotate_info(char *data, int *line, int *shift);
void print_pad(char pad[6][50], int *sum);
void ops_rect(char pad[6][50], int x, int y);
void ops_row(char pad[6][50], int y, int shift);
void ops_col(char pad[6][50], int x, int shift);

void ops_col(char pad[6][50], int x, int shift)
{
  int i;
  char tmp[6];
  
  for (i=0; i<6; i++)
  {
    tmp[i] = pad[i][x];
  }

  for (i=0; i<6; i++)
  {
    pad[(i+shift)%6][x] = tmp[i];
  }
}

void ops_row(char pad[6][50], int y, int shift)
{
  int i;
  char tmp[50];

  for (i=0; i<50; i++)
  {
    tmp[i] = pad[y][i];
  }

  for (i=0; i<50; i++)
  {
    pad[y][(i+shift)%50] = tmp[i]; 
  }
}

void ops_rect(char pad[6][50], int x, int y)
{
  int i, j;
  for (i=0; i<y; i++)
  {
    for (j=0; j<x; j++)
    {
      pad[i][j] = '*';
    }
  }
}

void print_pad(char pad[6][50], int *sum)
{
  int i, j;
  for (i=0; i<6; i++)
  {
    for (j=0; j<50; j++)
    {
      printf("%c ", pad[i][j]);
      if (pad[i][j] == '*')
      {
        (*sum)++;
      }
    }
    printf("\n");
  }
  printf("\n");
}

void get_rotate_info(char *data, int *line, int *shift)
{
  char *pos;

  pos = strstr(data, "=");
  *line = atoi(pos+1);
  pos = strstr(data, "by");
  *shift = atoi(pos+3);
}

void get_rect_info(char *data, int *x, int *y)
{
  char *pos;

  *x = atoi(data+5);
  pos = strstr(data, "x");
  *y = atoi(pos+1);
}

int main(int argc, char **argv)
{
  FILE *fp;
  char data[256];
  int x, y;
  int line, shift;
  char pad[6][50];
  int i, j;
  int sum = 0;

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

  for (i=0; i<6; i++)
  {
    for (j=0; j<50; j++)
    {
      pad[i][j] = '.';
    }
  }

  fgets(data, 256, fp);
  while (!feof(fp))
  {
    printf("%s", data);
    if ((strstr(data, "rect")) != NULL)
    {
      get_rect_info(data, &x, &y);
      printf("r %d %d\n", x, y);
      ops_rect(pad, x, y);
    }
    else if ((strstr(data, "rotate row")) != NULL)
    {
      get_rotate_info(data, &line, &shift);
      printf("rotate row %d %d\n", line , shift);
      ops_row(pad, line, shift);
    }
    else if ((strstr(data, "rotate column")) != NULL)
    {
      get_rotate_info(data, &line, &shift);
      printf("rotate column %d %d\n", line, shift);
      ops_col(pad, line, shift);
    }
    fgets(data, 256, fp);
  }

  print_pad(pad, &sum);
  printf("sum is: %d\n", sum);

  fclose(fp);
  return 0;
}
