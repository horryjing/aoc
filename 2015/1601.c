#include "stdio.h"
#include "string.h"

#define DATA_LEN 64
#define REQ_NUM 10

typedef struct element_t
{
  char name[16];
  char num;
}element;

element req[REQ_NUM];

int init_elements();
int get_num(char *p);

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  int i = 0;
  char *p = NULL;

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

  init_elements();

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    //printf("%s", data);
    for (i=0; i<REQ_NUM; i++)
    {
      if ((p = strstr(data, req[i].name)) != NULL)
      {
        //printf("%s----", req[i].name);
        p += strlen(req[i].name) + 2;
        if (get_num(p) != req[i].num)
        {
          break;
        }
        //printf("%d\n", req[i].num);
      }
    }
    if (i == REQ_NUM)
    {
      printf("---------%s\n", data);
    }
  }

  fclose(fp);
  return 0;
}

int init_elements()
{
  strcpy(req[0].name, "children");
  req[0].num = 3;
  strcpy(req[1].name, "cats");
  req[1].num = 7;
  strcpy(req[2].name, "samoyeds");
  req[2].num = 2;
  strcpy(req[3].name, "pomeranians");
  req[3].num = 3;
  strcpy(req[4].name, "akitas");
  req[4].num = 0;
  strcpy(req[5].name, "vizslas");
  req[5].num = 0;
  strcpy(req[6].name, "goldfish");
  req[6].num = 5;
  strcpy(req[7].name, "trees");
  req[7].num = 3;
  strcpy(req[8].name, "cars");
  req[8].num = 2;
  strcpy(req[9].name, "perfumes");
  req[9].num = 1;
  return 0;
}

int get_num(char *p)
{
  int num = 0;

  while ((*p>='0') && (*p<='9'))
  {
    num *= 10;
    num += *p - '0';
    p++;
  }

  return num;
}
