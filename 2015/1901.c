#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 1024
#define REPLACE_NUM 43
//#define REPLACE_NUM 3

typedef struct replace_t
{
  char org[4];
  char dest[16];
}replace;

typedef struct molecule_t
{
  char m[1024];
  struct molecule_t *next;
}molecule;

char *format = "%s => %s";
replace rep[REPLACE_NUM] = {0};
molecule *head = NULL;

int add(char *input);
int show();
int exist(char *input);
int gen(char *data);
int count();
int free_list();

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  char org[4] = {0};
  char dest[16] = {0};
  int i = 0;
  char *p = NULL;

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

  i = 0;
  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("%s", data);
    sscanf(data, format, org, dest);
    strcpy(rep[i].org, org);
    strcpy(rep[i].dest, dest);
    i++;
  }
  printf("%d\n", i);
  for (i--;i>=0; i--)
  {
    printf("%s -> %s\n", rep[i].org, rep[i].dest);
  }

  fclose(fp);

  if ((fp = fopen(argv[2], "r")) == NULL)
  {
    printf("failed to input file.\n");
    return 0;
  }

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("origin:\n");
    printf("%s", data);
  }
  
  gen(data);

  printf("cnt: %d\n", count());

  free_list();
  fclose(fp);
  return 0;
}

int add(char *input)
{
  molecule *p = NULL;

  if (exist(input) == 1)
  {
    return 0;
  }

  p = (molecule *)calloc(1, sizeof(molecule));
  strcpy(p->m, input);
  p->next = NULL;

  if (head == NULL)
  {
    head = p;
  }
  else
  {
    p->next = head;
    head = p;
  }

  return 0;
}

int show()
{
  molecule *p = head;

  while (p!=NULL)
  {
    printf("%s\n\n\n", p->m);
    p = p->next;
  }

  return 0;
}

int exist(char *input)
{
  molecule *p = head;

  while (p != NULL)
  {
    if (strcmp(input, p->m) == 0)
    {
      return 1;
    }
    p = p->next;
  }

  return 0;
}

int gen(char *data)
{
  char *p = data;
  int i = 0;
  char tmp1[1024] = {0};
  int p1 = 0;
  char buf[1024] = {0};
  int len = 0;

  while ((*p!='\r') && (*p!='\n'))
  {
    for (i=0; i<REPLACE_NUM; i++)
    {
      len = strlen(rep[i].org);
      if (strncmp(p, rep[i].org, len) == 0)
      {
        strcpy(buf, tmp1);
        strcat(buf, rep[i].dest);
        strcat(buf, p+len);
        add(buf);
        memset(buf, 0, sizeof(char)*1024);
      }
    }
    tmp1[p1] = *p;
    p++;
    p1++;
  }

  return 0;
}

int count()
{
  int cnt = 0;
  molecule *p = head;

  while (p != NULL)
  {
    cnt++;
    p = p->next;
  }

  return cnt;
}

int free_list()
{
  molecule *p = head;

  while (p != NULL)
  {
    head = p->next;
    free(p);
    p = head;
  }

  return 0;
}
