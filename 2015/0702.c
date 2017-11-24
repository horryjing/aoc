#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 64

typedef unsigned short u16;
typedef struct node_t
{
  char name[3];
  u16 value;
  u16 is_valid;
  struct node_t *next;
}node;

char pmov1[] = "%d -> %s";
char pmov2[] = "%s -> %s";
char pand1[] = "%d AND %s -> %s";
char pand2[] = "%s AND %s -> %s";
char plsft[] = "%s LSHIFT %d -> %s";
char prsft[] = "%s RSHIFT %d -> %s";
char pnot[] = "NOT %s -> %s";
char por[] = "%s OR %s -> %s";

node *head = NULL;

int mov1(u16 im, char *dst);
int mov2(char *src1, char *dst);
int and1(u16 im, char *src1, char *dst);
int and2(char *src1, char *src2, char *dst);
int lsft(char *src1, u16 im, char *dst);
int rsft(char *src1, u16 im, char *dst);
int not(char *src1, char *dst);
int or(char *src1, char *src2, char *dst);
node *find(char *name);
node *add(char *name);
int free_node();

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  char src1[3] = {0};
  char src2[3] = {0};
  char dst[3] = {0};
  u16 im = 0;
  node *p = NULL;
  int complete = 0;

  if (argc != 3)
  {
    printf("invalid input.\n");
    return 0;
  }

START_AGAIN:
  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    printf("failed to input file.\n");
    return 0;
  }

  complete = 0;

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    //printf("%s", data);
    if (sscanf(data, pmov1, &im, &dst) == 2)
    {
      if (mov1(im, dst) == -1)
      {
        complete = -1;
      }
    }
    else if (sscanf(data, pmov2, &src1, &dst) == 2)
    {
      if (mov2(src1, dst) == -1)
      {
        complete = -1;
      }
    }
    else if (sscanf(data, pand1, &im, &src1, &dst) == 3)
    {
      if (and1(im, src1, dst) == -1)
      {
        complete = -1;
      }
    }
    else if (sscanf(data, pand2, &src1, &src2, &dst) == 3)
    {
      if (and2(src1, src2, dst) ==  -1)
      {
        complete = -1;
      }
    }
    else if (sscanf(data, plsft, &src1, &im, &dst) == 3)
    {
      if (lsft(src1, im, dst) == -1)
      {
        complete = -1;
      }
    }
    else if (sscanf(data, prsft, &src1, &im, &dst) == 3)
    {
      if (rsft(src1, im, dst) == -1)
      {
        complete = -1;
      }
    }
    else if (sscanf(data, pnot, &src1, &dst) == 2)
    {
      if (not(src1, dst) == -1)
      {
        complete = -1;
      }
    }
    else if (sscanf(data, por, &src1, &src2, &dst) == 3)
    {
      if (or(src1, src2, dst) == -1)
      {
        complete = -1;
      }
    }
    else
    {
      printf("error input\n");
      break;
    }
  }

  if (complete == -1)
  {
    fclose(fp);
    goto START_AGAIN;
  }

  p = find(argv[2]);
  printf("\n%d\n", p->value);
  
  free_node();
  fclose(fp);
  return 0;
}

int mov1(u16 im, char *dst)
{
  node *p = NULL;

  //printf("%d %s\n", im, dst);
  p = find(dst);
  p->value = im;
  p->is_valid = 1;
  printf("%s->value = %d\n", dst, p->value);

  return 0;
}

int mov2(char *src1, char *dst)
{
  node *p1 = NULL;
  node *p2 = NULL;

  //printf("%s %s\n", src1, dst);
  p1 = find(src1);
  p2 = find(dst);
  if (p1->is_valid == 0)
  {
    printf("%s is invalid.\n", p1);
    return -1;
  }
  p2->value = p1->value;
  p2->is_valid = 1;
  printf("%s->value = %d\n", dst, p2->value);
  
  return 0;
}
int and1(u16 im, char *src1, char *dst)
{
  node *p1 = NULL;
  node *p2 = NULL;

  //printf("%s %s\n", src1, dst);
  p1 = find(src1);
  p2 = find(dst);
  if (p1->is_valid == 0)
  {
    printf("%s is invalid.\n", p1);
    return -1;
  }
  p2->value = im & p1->value;
  p2->is_valid = 1;
  printf("%s->value = %d\n", dst, p2->value);

  return 0;
}
int and2(char *src1, char *src2, char *dst)
{
  node *p1 = NULL;
  node *p2 = NULL;
  node *p3 = NULL;

  //printf("%s %s %s\n", src1, src2, dst);
  p1 = find(src1);
  p2 = find(src2);
  p3 = find(dst);
  if (p1->is_valid == 0)
  {
    printf("%s is invalid.\n", p1);
    return -1;
  }
  if (p2->is_valid == 0)
  {
    printf("%s is invalid.\n", p2);
    return -1;
  }
  p3->value = p1->value & p2->value;
  p3->is_valid = 1;
  printf("%s->value = %d\n", dst, p3->value);

  return 0;
}
int lsft(char *src1, u16 im, char *dst)
{
  node *p1 = NULL;
  node *p2 = NULL;

  //printf("%s %d %s\n", src1, im, dst);
  p1 = find(src1);
  p2 = find(dst);
  if (p1->is_valid == 0)
  {
    printf("%s is invalid.\n", p1);
    return -1;
  }
  p2->value = p1->value << im;
  p2->is_valid = 1;
  printf("%s->value = %d\n", dst, p2->value);

  return 0;
}
int rsft(char *src1, u16 im, char *dst)
{
  node *p1 = NULL;
  node *p2 = NULL;

  //printf("%s %d %s\n", src1, im, dst);
  p1 = find(src1);
  p2 = find(dst);
  if (p1->is_valid == 0)
  {
    printf("%s is invalid.\n", p1);
    return -1;
  }
  p2->value = p1->value >> im;
  p2->is_valid = 1;
  printf("%s->value = %d\n", dst, p2->value);

  return 0;
}

int not(char *src1, char *dst)
{
  node *p1 = NULL;
  node *p2 = NULL;

  //printf("%s %s\n", src1, dst);
  p1 = find(src1);
  p2 = find(dst);
  if (p1->is_valid == 0)
  {
    printf("%s is invalid.\n", p1);
    return -1;
  }
  p2->value = ~p1->value;
  p2->is_valid = 1;
  printf("%s->value = %d\n", dst, p2->value);

  return 0;
}

int or(char *src1, char *src2, char *dst)
{
  node *p1 = NULL;
  node *p2 = NULL;
  node *p3 = NULL;

  //printf("%s %s %s\n", src1, src2, dst);
  p1 = find(src1);
  p2 = find(src2);
  p3 = find(dst);
  if (p1->is_valid == 0)
  {
    printf("%s is invalid.\n", p1);
    return -1;
  }
  if (p2->is_valid == 0)
  {
    printf("%s is invalid.\n", p2);
    return -1;
  }
  p3->value = p1->value | p2->value;
  p3->is_valid = 1;
  printf("%s->value = %d\n", dst, p3->value);

  return 0;
}

node *find(char *name)
{
  node *p = head;
  while (p != NULL)
  {
    if (strcmp(p->name, name) == 0)
    {
      break;
    }
    p = p->next;
  }

  if (p == NULL)
  {
    printf("add %s\n", name);
    p = add(name);
    if (strcmp(p->name, "b") == 0)
    {
      p->value = 3176;
      p->is_valid = 1;
      printf("init %s->value = 3176\n", p->name);
    }
  }
  
  return p;
}

node *add(char *name)
{
  node *p = NULL;

  p = (node *)malloc(sizeof(node));
  strcpy(p->name, name);
  p->value = 0;
  p->is_valid = 0;
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

  return p;
}

int free_node()
{
  node *p = head;

  while (p != NULL)
  {
    head = p->next;
    free(p);
    p = head;
  }

  return 0;
}
