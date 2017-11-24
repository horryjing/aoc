#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 64
#define UNKNOWN_VAL -1
#define TYPE_BOT 1
#define TYPE_BIN 2

typedef struct bot_t{
  int id;
  int type; /*1: bot, 2: bin*/
  int chip1; /*low value*/
  int chip2; /*high value*/
  struct bot_t *low_bot;
  struct bot_t *high_bot;
  struct bot_t *next;
}bot;

bot *head = NULL;

void set_chip(bot *t, int chip);
void set_relate(bot *t, bot *low_bot, bot *high_bot);
bot *find_bot(int id, int type);
void parse(char *data);
void free_list();
int check(bot *tmp);
int run();

void set_chip(bot *t, int chip)
{
  int tmp = t->chip1;

  if (tmp == UNKNOWN_VAL)
  {
    t->chip1 = chip;
  }
  else
  {
    if (tmp < chip)
    {
      t->chip2 = chip;
    }
    else
    {
      t->chip1 = chip;
      t->chip2 = tmp;
    }
  }
}

void set_relate(bot* t, bot *low_bot, bot *high_bot)
{
    t->low_bot = low_bot;
    t->high_bot = high_bot;
}

bot *find_bot(int id, int type)
{
  bot *tmp;

  tmp = head;
  while (tmp != NULL)
  {
    if ((tmp->id == id) && (tmp->type == type))
    {
      break;
    }
    tmp = tmp->next;
  }

  if (tmp == NULL)/*create new one*/
  {
    tmp = (bot *)malloc(sizeof(bot));
    memset(tmp, 0, sizeof(bot));
    tmp->id = id;
    tmp->type = type;
    tmp->chip1 = UNKNOWN_VAL;
    tmp->chip2 = UNKNOWN_VAL;
    tmp->low_bot = NULL;
    tmp->high_bot = NULL;
    tmp->next = head;
    head = tmp;
  }

  return tmp;
}

void parse(char *data)
{
  int id, chip;
  int bot_low, bot_high;
  int bin_low, bin_high;
  char *format1 = "value %d goes to bot %d";
  char *format2 = "bot %d gives low to bot %d and high to bot %d";
  char *format3 = "bot %d gives low to output %d and high to output %d";
  char *format4 = "bot %d gives low to output %d and high to bot %d";
  bot *tmp1;
  bot *tmp2;
  bot *tmp3;

  /*value %d goes to bot %d*/
  if (sscanf(data, format1, &chip, &id) == 2)
  {
    //printf("%d %d\n", chip, id);
    tmp1 = find_bot(id, TYPE_BOT);
    set_chip(tmp1, chip);
  }
  /*bot %d gives low to bot %d and high to bot %d*/
  else if (sscanf(data, format2, &id, &bot_low, &bot_high) == 3)
  {
    //printf("%d %d %d\n", id, bot_low, bot_high);
    tmp1 = find_bot(id, TYPE_BOT);
    tmp2 = find_bot(bot_low, TYPE_BOT);
    tmp3 = find_bot(bot_high, TYPE_BOT);
    set_relate(tmp1, tmp2, tmp3);
  }
  /*bot %d gives low to output %d and high to output %d*/
  else if (sscanf(data, format3, &id, &bin_low, &bin_high) == 3)
  {
    //printf("%d %d %d\n", id, bin_low, bin_high);
    tmp1 = find_bot(id, TYPE_BOT);
    tmp2 = find_bot(bin_low, TYPE_BIN);
    tmp3 = find_bot(bin_high, TYPE_BIN);
    set_relate(tmp1, tmp2, tmp3);
  }
  /*bot %d gives low to output %d and high to bot %d*/
  else if (sscanf(data, format4, &id, &bin_low, &bot_high) == 3)
  {
    //printf("%d %d %d\n", id, bin_low, bot_high);
    tmp1 = find_bot(id, TYPE_BOT);
    tmp2 = find_bot(bin_low, TYPE_BIN);
    tmp3 = find_bot(bot_high, TYPE_BOT);
    set_relate(tmp1, tmp2, tmp3);
  }
  else
  {
    printf("***************ERROR******************\n");
  }
}

void free_list()
{
  bot *tmp;
  tmp = head;
  while (tmp != NULL)
  {
    head = tmp->next;
    free(tmp);
    tmp = head;
  }
}
int check(bot *tmp)
{
  int found = -1;

  if ((tmp->chip1 != UNKNOWN_VAL)
    &&(tmp->chip2 != UNKNOWN_VAL)
    &&(tmp->type == TYPE_BOT)
    &&(tmp->low_bot != NULL)
    &&(tmp->high_bot != NULL))
  {
    if ((tmp->chip1 == 17) && (tmp->chip2 == 61))
    {
      printf("*******found*********\n");
      return tmp->id;
    }
    printf("tmp->id %d\n", tmp->id);
    set_chip(tmp->low_bot, tmp->chip1);
    set_chip(tmp->high_bot, tmp->chip2);
    tmp->chip1 = UNKNOWN_VAL;
    tmp->chip2 = UNKNOWN_VAL;

    found = check(tmp->low_bot);
    if (found != -1)
    {
      return found;
    }
    else
    {
      found = check(tmp->high_bot);
      return found;
    }
  }
  return -1;
}

int run()
{
  bot *tmp;
  int found = -1;

  tmp = head;
  while (found == -1)
  {
    printf("run check\n");
    found = check(tmp);
    tmp =tmp->next;
    if (tmp == NULL)
    {
      tmp = head;
    }
  }
  return found;
}

int main(int argc, char **argv)
{
  FILE *fp;
  char data[DATA_LEN];
  bot *tmp;
  int found = -1;

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
    //printf("%s", data);
    parse(data);
  }

  found = run();

  printf("found: %d\n", found);
  free_list();

  fclose(fp);
  return 0;
}
