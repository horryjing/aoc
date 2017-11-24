#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define DATA_LEN 64

typedef struct disc_t
{
  int num;
  int period;
  int pos;
  struct disc_t *next;
}disc;

disc *head = NULL;

disc *create_disc(int d, int period, int init_pos);
int check_time(int slot);
void free_list();


int main(int argc, char **argv)
{
  FILE *fp;
  char data[DATA_LEN];
  int d;
  int period;
  int init_pos;
  disc *tmp;
  disc *tail;
  int slot = 0;

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

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("%s", data);
    sscanf(data, "Disc #%d has %d positions; at time=0, it is at position %d.", 
      &d, &period, &init_pos);
    printf("%d, %d, %d\n", d, period, init_pos);
    tmp = create_disc(d, period, init_pos);
    if (head == NULL)
    {
      head = tmp;
      tail = tmp;
    }
    else
    {
      tail->next = tmp;
      tail = tmp;
    }
  }

  //add new disc
  tmp = create_disc(0, 11, 0);
  tail->next = tmp;
  tail = tmp;

  while (check_time(slot) != 0)
  {
    slot++;
  }

  printf("time slot is %d\n", slot);

  free_list();
  fclose(fp);
  return 0;
}

disc *create_disc(int d, int period, int init_pos)
{
  disc *tmp = NULL;

  tmp = (disc *)malloc(sizeof(disc));
  tmp->num = d;
  tmp->period = period;
  tmp->pos = init_pos;
  tmp->next = NULL;

  return tmp;
}

int check_time(int slot)
{
  disc *p = head;

  while (p!=NULL)
  {
    slot++;
    if (((p->pos+slot)%p->period) == 0)
    {
      p = p->next;
    }
    else
    {
      return -1;
    }
  }

  return 0;
}

void free_list()
{
  disc *tmp = head;
  while (tmp!=NULL)
  {
    head = tmp->next;
    free(tmp);
    tmp = head;
  }
}

