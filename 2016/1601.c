#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BUF_SIZE 36651585

void calc(char *data, int len);

int main(int argc, char **argv[])
{
  char *data;
  int len = 0;

  if (argc != 3)
  {
    printf("invalid input.\n");
  }

  data = (char *)argv[1];
  len = atoi(argv[2]);
  printf("input: %s, %d\n", data, len);

  calc(data, len);

  return 0;
}

void calc(char *data, int len)
{
  char *chksum = NULL;
  char *buf = NULL;
  int cur_len = 0;
  int i = 0;
  int cnt = 0;

  chksum = (char *)malloc(BUF_SIZE);
  buf = (char *)malloc(BUF_SIZE);
  memset(chksum, 0, BUF_SIZE);
  memset(buf, 0, BUF_SIZE);

  strcpy(buf, data);
  cur_len = strlen(buf);
  printf("%s, %d\n", buf, cur_len);

  while (cur_len < len)
  {
    buf[cur_len] = '0';
    for (i=0; i<cur_len; i++)
    {
      if (buf[i] == '1')
      {
        buf[2*cur_len-i] = '0';
      }
      else
      {
        buf[2*cur_len-i] = '1';
      }
    }
    cur_len = strlen(buf);
  }

  if (cur_len > len)
  {
    buf[len] = '\0';
  }

  strcpy(chksum, buf);
  cur_len = strlen(chksum);
  while (cnt%2 == 0)
  {
    cnt = 0;
    for (i=0; i<cur_len; i+=2)
    {
      if (chksum[i] == chksum[i+1])
      {
        chksum[i/2] = '1';
      }
      else
      {
        chksum[i/2] = '0';
      }
      cnt++;
    }
    chksum[i/2] = '\0';
    cur_len = strlen(chksum);
  }
  printf("result: %s\n", chksum);
  return;
}
