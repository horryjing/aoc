#include "stdio.h"
#include "string.h"

#define DATA_LEN 16
#define OPS_LEN 47

char ops[OPS_LEN][16] = {0};
int reg[2] = {1, 0};
int pc = 0;
int run();

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  int i = 0;

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

  i = 0;
  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    strcpy(ops[i], data);
    printf("%s", ops[i]);
    i++;
  }

  run();
  printf("%d\n", reg[1]);

  fclose(fp);
  return 0;
}

int run()
{
  while (pc < OPS_LEN)
  {
    execute(ops[pc]);
  }

  return 0;
}

int execute(char *com)
{
  char r = 0;
  char f = 0;
  int o = 0;
  int offset = 0;

  if (sscanf(com, "jio %c, %c%d", &r, &f, &o) == 3)
  {
    offset = o;
    if (f == '-')
    {
      offset = -o;  
    }
    if (reg[r-'a'] == 1)
    {
      pc += offset;
    }
    else
    {
      pc++;
    }
  }
  else if (sscanf(com, "inc %c", &r) == 1)
  {
    reg[r-'a']++;
    pc++;
  }
  else if (sscanf(com, "tpl %c", &r) == 1)
  {
    reg[r-'a'] *= 3;
    pc++;
  }
  else if (sscanf(com, "hlf %c", &r) == 1)
  {
    reg[r-'a'] /= 2;
    pc++;
  }
  else if (sscanf(com, "jmp %c%d", &f, &o) == 2)
  {
    offset = o;
    if (f == '-')
    {
      offset = -o;
    }
    pc += offset;
  }
  else if (sscanf(com, "jie %c, %c%d", &r, &f, &o) == 3)
  {
    offset = o;
    if (f == '-')
    {
      offset = -o;
    }
    if (reg[r-'a']%2==0)
    {
      pc += offset;
    }
    else
    {
      pc++;
    }
  }
  else
  {
    printf("invalid ops: %s\n", com);
  }
  printf("%s %d %d %d\n", com, reg[0], reg[1], pc);
  return 0;
}
