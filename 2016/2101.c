#include "stdio.h"
#include "string.h"

#define DATA_LEN 64
#define STR_LEN 16

char *rp = "reverse positions %d through %d";
char *rop = "rotate based on position of letter %c";
char *swp = "swap position %d with position %d";
char *mp = "move position %d to position %d";
char *swl = "swap letter %c with letter %c";
char *ror = "rotate right %d steps";
char *rol = "rotate left %d steps";

void op(char *input, char *inst);

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  char input[STR_LEN] = {0};

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
  strcpy(input, argv[2]);
  printf("input string: %s\n", input);

  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    printf("%s", data);
    op(input, data);
    printf("%s\n", input);
  }

  printf("result: %s\n", input);
  fclose(fp);
  return 0;
}

void op(char *input, char *inst)
{
  int p1 = 0;
  int p2 = 0;
  char l1 = 0;
  char l2 = 0;
  int steps = 0;
  char tmp[STR_LEN] = {0};
  int len = strlen(input);
  int i = 0;
  int temp = 0;
  int cnt = 0;

  strcpy(tmp, input);

  if (sscanf(inst, swp, &p1, &p2) == 2)
  {
    printf(swp, p1, p2);
    printf("\n");
    p1 %= len;
    p2 %= len;
    input[p1] = tmp[p2];
    input[p2] = tmp[p1];
  }
  else if (sscanf(inst, swl, &l1, &l2) == 2)
  {
    printf(swl, l1, l2);
    printf("\n");
    for (i=0; i<len; i++)
    {
      if (input[i] == l1)
      {
        input[i] = l2;
      }
      else if (input[i] == l2)
      {
        input[i] = l1;
      }
    }
  }
  else if (sscanf(inst, rol, &steps) == 1)
  {
    printf(rol, steps);
    printf("\n");
    steps %= len;
    for (i=0; i<len; i++)
    {
      if (i-steps < 0)
      {
        input[i+len-steps] = tmp[i];
      }
      else
      {
        input[i-steps] = tmp[i];
      }
    }
  }
  else if (sscanf(inst, ror, &steps) == 1)
  {
    printf(ror, steps);
    printf("\n");
    steps %= len;
    for (i=0; i<len; i++)
    {
      if (i+steps >= len)
      {
        input[i+steps-len] = tmp[i];
      }
      else
      {
        input[i+steps] = tmp[i];
      }
    }
  }
  else if (sscanf(inst, rop, &l1) == 1)
  {
    printf(rop, l1);
    printf("\n");
    //find index
    for (cnt=0; input[cnt]!=l1; cnt++)
    {
    }
    //add one if at least 4
    if (cnt >= 4)
    {
      cnt++;
    }
    //add one for first rotate once
    cnt++;
    cnt %= len;
    for (i=0; i<len; i++)
    {
      if (i+cnt >= len)
      {
        input[i+cnt-len] = tmp[i];
      }
      else
      {
        input[i+cnt] = tmp[i];
      }
    }
    
  }
  else if (sscanf(inst, rp, &p1, &p2) == 2)
  {
    printf(rp, p1, p2);
    printf("\n");
    p1 %= len;
    p2 %= len;
    if (p1 > p2)
    {
      temp = p1;
      p1 = p2;
      p2 = temp;
    }
    temp = p2 - p1;
    cnt = 0;
    while (cnt <= temp)
    {
      input[p2-cnt] = tmp[p1+cnt];
      cnt++;
    }
  }
  else if (sscanf(inst, mp, &p1, &p2) == 2)
  {
    printf(mp, p1, p2);
    printf("\n");
    p1 %= len;
    p2 %= len;
    if (p1 > p2)
    {
      for (i=p2; i<len; i++)
      {
        if (i<p1 && i>=p2)
        {
          input[i+1] = tmp[i];
        }
      }
    }
    if (p1 < p2)
    {
      for (i=p1; i<len; i++)
      {
        if (i>p1 && i<=p2)
        {
          input[i-1] = tmp[i];
        }
      }
    }
    input[p2] = tmp[p1];
  }
  else
  {
    printf("*******missed instruction*******\n");
  }
}
