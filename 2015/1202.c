#include "stdio.h"

#define DATA_LEN 30000
#define Q_LEN 10000
#define SQR_BGN 0xFC
#define SQR_END 0xFD
#define BRC_BGN 0xFE
#define BRC_END 0xFF
#define FAIL 0xFFFF
#define OK 0xFFFE
#define INVALID 0xFFFC

int queue[Q_LEN] = {0};
int point = 0; //point to the latest element

int is_digital(char c);
int sum(char *data);
int push(int n);
int pop();

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  int cnt = 0;
  char *p = data;
  int nagtive = 0;
  int num = INVALID;
  int in_brace = 0;
  int is_red = 0;

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
  }

  while (*p != '\n')
  {
    if ((*p == '-') && (is_digital(*(p+1))))
    {
      nagtive = 1;
      p++;
      continue;
    }
    if (is_digital(*p))
    {
      if (num == INVALID)
      {
        num = 0;
      }
      num *= 10;
      num += *p - '0';
      p++;
      continue;
    }
    if (nagtive == 1)
    {
      num = -num;
    }
    if (num != INVALID)
    {
      push(num);
      num = INVALID;
      nagtive = 0;
    }

    if (*p == '[')
    {
      push(SQR_BGN);
      p++;
      continue;
    }
    else if (*p == '{')
    {
      push(BRC_BGN);
      in_brace = 1;
      p++;
      continue;
    }
    else if (*p == ']')
    {
      while (queue[point] != SQR_BGN)
      {
        if (in_brace == 1 && is_red)
        {
          pop();
        }
        else
        {
          cnt += pop();
        }
      }
      pop();//pop SQR_BGN
      p++;
      continue;
    }
    else if (*p == '}')
    {
      while (queue[point] != BRC_BGN)
      {
        if (in_brace == 1 && is_red)
        {
          pop();
        }
        else
        {
          cnt += pop();
        }
      }
      pop();//pop BRC_BGN
      in_brace = 0;
      is_red = 0;
      p++;
      continue;
    }
    else if ((*p=='r') && (*(p+1)=='e') && (*(p+2)='d'))
    {
      is_red = 1;
      p += 3;
      continue;
    }
    p++;
  }

  printf("cnt %d\n", cnt);

  fclose(fp);
  return 0;
}

int is_digital(char c)
{
  if (c>='0' && c<='9')
  {
    return 1;
  }
  return 0;
}

int push(int n)
{
  if (point < 0 || point >= Q_LEN-1)
  {
    printf("PUSH: beyond queue range, point %d.\n", point);
    return FAIL;
  }
  point++;
  queue[point] = n;

  return OK;
}

int pop()
{
  int value = 0;

  if (point < 0 || point > Q_LEN-1)
  {
    printf("POP: beyonde queue range, point %d\n", point);
    return FAIL;
  }

  value = queue[point];
  point--;

  return value;
}
