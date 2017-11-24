#include "stdio.h"
#include "string.h"

int main(int argc, char **argv)
{
  FILE *fp;
  char data[16];
  unsigned int cnt[8][26];
  int i, j, min_index = 0;
  char *ptr;

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

  memset(cnt, 0, sizeof(cnt));
  while(fscanf(fp, "%s ", data) != EOF)
  {
    printf("%s\n", data);

    ptr = data;
    for (i=0; i<8; i++)
    {
      cnt[i][*ptr-'a']++;
      printf("%d, %d, %d\n", i, *ptr-'a', cnt[i][*ptr-'a']);
      ptr++;
    }
  }

  for (i=0; i<8; i++)
  {
    min_index = 0;
    for (j=0; j<26; j++)
    {
      if ((cnt[i][j] <= cnt[i][min_index])
           && (cnt[i][j] > 0))
      {
        min_index = j;
      }
    }
    printf("%c", min_index+'a');
  }

  printf("\n");

  fclose(fp);
  return 0;
}
