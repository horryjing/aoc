#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 96

typedef struct reindeer_t
{
  char name[16];
  int speed;
  int fly_time;
  int rest_time;
  struct reindeer_t *next;
}reindeer;

char *format = "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.";
reindeer *head = NULL;

int add(char *input);
void race(int s);
void free_list();
int computer();

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  reindeer *p = NULL;
  int seconds = 0;

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
  seconds = atoi(argv[2]);

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("%s", data);
    add(data);        
  }

  race(seconds);

  free_list();
  fclose(fp);
  return 0;
}

int add(char *input)
{
  reindeer *p = NULL;
  char name[16] = {0};
  int speed = 0;
  int fly_time = 0;
  int rest_time = 0;

  p = (reindeer *)malloc(sizeof(reindeer));
  memset(p, 0, sizeof(reindeer));

  sscanf(input, format, name, &speed, &fly_time, &rest_time);

  strcpy(p->name, name);
  p->speed = speed;
  p->fly_time = fly_time;
  p->rest_time = rest_time;
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

void race(int s)
{
  reindeer *p = head;
  int time = 0;
  int dist = 0;

  while (p != NULL)
  {
    time = p->fly_time + p->rest_time;
    dist = (s/time)*p->fly_time*p->speed;
    if (s%time>=p->fly_time)
    {
      dist += p->fly_time * p->speed;
    }
    else
    {
      dist += (s%time) * p->speed;
    }
    printf("%s %d %d %d %d\n", p->name, p->speed, p->fly_time, p->rest_time, dist);
    p = p->next;
  }
}

void free_list()
{
  reindeer *p = head;

  while (p != NULL)
  {
    head = p->next;
    free(p);
    p = head;
  }
}
