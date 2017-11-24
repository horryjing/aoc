#include "stdio.h"
#include "stdlib.h"

typedef struct elf_t
{
  int id;
  struct elf_t *next;
}elf;

elf *head = NULL;

void init_elves(int num);
void free_elves();

int main(int argc, char **argv)
{
  int num = 0;
  int cnt = 0;
  elf *cur = 0;
  elf *left = 0;

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }
  num = atoi(argv[1]);

  init_elves(num);

  cnt = num / 2;
  cur = head;
  left = cur;
  while (num != 1)
  {
    left = left->next;


  }

  free_elves();

  return 0;
}

void init_elves(int num)
{
  elf *p = NULL;
  elf *pre = NULL;
  int i = 0;

  printf("num %d\n", num);
  for (i=0; i<num; i++)
  {
    p = (elf *)malloc(sizeof(elf));
    p->id = i + 1;
    if (head == NULL)
    {
      p->next = NULL;
      head = p;
      pre = p;
    }
    else
    {
      pre->next = p;
      pre = p;
    }
  }
  pre->next = head;
}

void free_elves()
{
  elf *p = NULL;
  elf *tmp = NULL;

  p = head;
  tmp = head;

  while (p != NULL)
  {
    tmp = p->next;
    p->id = 0;
    p->next = NULL;
    if (tmp == NULL) break;
    free(p);
    p = tmp;
  }
}
