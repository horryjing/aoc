#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 64
#define ROWS 33
#define COLS 31
#define SIZE ROWS*COLS

typedef struct node_t
{
  int r;
  int c;
  int used;
  int avail;
}node;

char *df = "/dev/grid/node-x%d-y%d %dT %dT %dT %d%%";

void print_list(node list[SIZE]);
int check_pair(node list[SIZE]);

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  node *list = NULL;
  int row = 0;
  int col = 0;
  int size = 0;
  int used = 0;
  int avail = 0;
  int percent = 0;
  int index = 0;

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

  list = (node *)malloc(SIZE*sizeof(node));
  memset(list, 0, SIZE*sizeof(node));

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("%s", data);
    if ((sscanf(data, df, &row, &col, &size, &used, &avail, &percent)) == 6) 
    {
      list[index].r = row;
      list[index].c = col;
      list[index].used = used;
      list[index].avail = avail;
      index++;
    }
    printf("index %d\n", index);
  }

  //print_list(list);
  printf("pair %d\n", check_pair(list));

  free(list);
  fclose(fp);
  return 0;
}

void print_list(node list[SIZE])
{
  int i = 0;
  
  for (i=0; i<SIZE; i++)
  {
    printf("node-%d-%d, %d, %d\n",
      list[i].r,
      list[i].c,
      list[i].used,
      list[i].avail);
  }
}

int check_pair(node list[SIZE])
{
  int cnt = 0;
  int i = 0;
  int j = 0;

  for (i=0; i<SIZE; i++)
  {
    for (j=0; j<SIZE; j++)
    {
      if ((i!=j) 
        && (list[i].used != 0)
        && (list[j].avail >= list[i].used))
      {
        cnt++;
      }
    }
  }

  return cnt;
}
