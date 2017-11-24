#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct aba_t{
  char a;
  char b;
  int hyper;
  struct aba_t *next;
}aba;

aba *head = NULL;
int list_num = 0;

int check_aba(char *str, int hyper);
void free_list();

void free_list()
{
  aba *tmp;
  tmp = head;
  while (tmp != NULL)
  {
    head = tmp->next;
    free(tmp);
    tmp = head;
  }
  head = NULL;
  list_num =0;
}

int check_aba(char *str, int hyper)
{
  int i;
  aba *tmp;

  for (i=0; i<strlen(str)-2; i++)
  {
    if ((str[i] == str[i+2])
       && (str[i] != str[i+1]))
    {
      tmp = head;
      while (tmp != NULL)
      {
        if ((tmp->a == str[i+1])
          &&(tmp->b == str[i])
          &&(tmp->hyper != hyper))
        {
          return 1;
        }
        tmp = tmp->next;
      }

      tmp = (aba *)malloc(sizeof(aba));
      tmp->a = str[i];
      tmp->b = str[i+1];
      tmp->hyper = hyper;
      tmp->next = head;
      head = tmp;
      list_num++;
    }
  }

  return 0;
}

int main(int argc, char **argv)
{
  FILE *fp;
  char data[256];
  int hyper = 0;
  char *ptr;
  int found = 0;
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

  while(fscanf(fp, "%s ", data)!=EOF)
  {
    printf("%s\n", data);

    ptr = strtok(data, "[]");
    while (ptr != NULL)
    {
      found = check_aba(ptr, hyper);
      ptr = strtok(NULL, "[]");
      if (found == 1)
      {
        ptr = NULL;
      }
      hyper = !hyper;
    }
    if (found == 1)
    {
      sum++;
    }
    hyper = 0;
    found = 0;
    free_list(head);
  }

  printf("sum is: %d.\n", sum);

  fclose(fp);
  return 0;
}
