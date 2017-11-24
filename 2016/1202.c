#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DATA_LEN 16
#define LINE 32
#define LEN 16

int re[4] = {0, 0, 1, 0};
int pc = 0;

void print_buf(char buf[LINE][LEN]);
void print_reg();
void parse(char *com, int *op, int **src, int **dst);
void print_parse(int op, int *src, int *dst);
void run(int op, int *src, int *dst);

int main(int argc, char **argv)
{
  FILE *fp;
  char data[DATA_LEN];
  int i;
  char buf[LINE][LEN];
  int *src;
  int *dst;
  int op;
  int imm1 = 0;
  int imm2 = 0;

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
  memset(buf, 0, LINE*LEN);
  while (fgets(data, DATA_LEN, fp) != NULL)
  {
    strcpy(buf[i], data);
    i++;
  }

  //print_buf(buf);

  while (buf[pc][0] != '\0')
  {
    src = &imm1;
    dst = &imm2;
    imm1 = 0;
    imm2 = 0;
    printf("line %d: %s", pc+1, buf[pc]);
    parse(buf[pc], &op, &src, &dst);
    print_parse(op, src, dst);
    run(op, src, dst);
    print_reg();
  }

  print_reg();

  fclose(fp);
  return 0;
}

void print_buf(char buf[LINE][LEN])
{
  int i;
  for (i=0; i<LINE; i++)
  {
    if (buf[i][0] == '\0')
    {
      break;
    }
    printf("line %d: %s", i, buf[i]);
  }
  printf("\n");
  return;
}

void print_reg()
{
  printf("a=%d, b=%d, c=%d, d=%d, pc=%d\n", re[0], re[1], re[2], re[3], pc);
}

//op: 1-cpy, 2-inc, 3-dec, 4-jnz
void parse(char *com, int *op, int **src, int **dst)
{
  char *p = com;
  int flag = 0;

  // set op
  if (*p == 'c')
  {
    *op = 1;
  }
  else if (*p == 'i')
  {
    *op = 2;
  }
  else if (*p == 'd')
  {
    *op = 3;
  }
  else if (*p == 'j')
  {
    *op = 4;
  }
  p += 4;
  
  //set src
  while (*p != ' ')
  {
    if (*p == '\r')
    {
      break;
    }
    if (*p>='a' && *p<='d')
    {
      *src = &re[*p-'a'];
    }
    else if (*p == '-')
    {
      flag = -1;
    }
    else if (*p>='0' && *p<='9')
    {
      **src *= 10;
      **src += *p - '0';
    }
    p++;
  }
  if (flag == -1)
  {
    **src *= flag;
  }

  //set dst
  while(*p != '\r')
  {
    if (*p>='a' && *p<='d')
    {
      *dst = &re[*p-'a'];
    }
    else if (*p == '-')
    {
      flag = -1;
    }
    else if (*p>='0' && *p<='9')
    {
      **dst *= 10;
      **dst += *p - '0';
    }
    p++;
  }
  if (flag == -1)
  {
    **dst *= flag;
  }
}

void print_parse(int op, int *src, int *dst)
{
  printf("op %d ", op);
  printf("src %d ", *src);
  if (dst != 0)
  {
    printf("dst %d ", *dst);
  }
  printf("\n");
}

void run(int op, int *src, int *dst)
{
  switch (op)
  {
    case 1:
    {
      *dst = *src;
      pc++;
      break;
    }
    case 2:
    {
      (*src)++;
      pc++;
      break;
    }
    case 3:
    {
      (*src)--;
      pc++;
      break;
    }
    case 4:
    {
      if (*src != 0)
      {
        pc += *dst;
      }
      else
      {
        pc++;
      }
      break;
    }
    default:
      printf("error op %d\n", op);
  }
}
