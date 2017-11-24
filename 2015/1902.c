#include "stdio.h"

#define DATA_LEN 1024

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char data[DATA_LEN] = {0};
  char *p = NULL;
  int cnt = 0;
  int cnt1 = 0;
  int cnt2 = 0;

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

  p = data;
  while ((*p!='\r') && (*p!='\n'))
  {
    if ((*p>='A') && (*p<='Z'))
    {
      cnt++;
    }
    if ((*p=='R') && (*(p+1)=='n'))
    {
      cnt1++;
    }
    if ((*p=='A') && (*(p+1)=='r'))
    {
      cnt1++;
    }
    if (*p=='Y')
    {
      cnt2++;
    }
    p++;
  }

  printf("cnt %d cnt1 %d cnt2 %d\n", cnt, cnt1, cnt2);
  printf("%d\n", cnt-cnt1-2*cnt2-1);

  fclose(fp);
  return 0;
}
