#include "stdio.h"
#include "string.h"

typedef unsigned int u32;

void parse_room(char *data, char *name, u32 *sector, char *checksum);
void check_sum(char *name, char *cs);

void check_sum(char *name, char *cs)
{
  char i, j;
  char letter[26] = {0};
  char *ptr;
  char max_index = 0;

  ptr = name;
  while (*ptr != '\0')
  {
    letter[*ptr-'a']++;
    ptr++;
  }

  for (i=0; i<5; i++)
  {
    for (j=0; j<26; j++)
    {
      if (letter[j] > letter[max_index])
      {
        max_index = j;
      }
    }
    letter[max_index] = 0;
    cs[i] = max_index + 'a';
  }
}

void parse_room(char *data, char *name, u32 *sector, char *checksum)
{
  char *ptr;
  char *tmp;

  ptr = data;
  tmp = name;
  while (!((*ptr >= '0') && (*ptr <= '9')))
  {
    if (*ptr == '-')
    {
      ptr++;
      continue;
    }
    *tmp = *ptr;
    tmp++;
    ptr++;
  }

  *sector = 0;
  while (*ptr != '[')
  {
    *sector *= 10;
    *sector += *ptr - '0';
    ptr++;
  }

  ptr++;
  tmp = checksum;
  while (*ptr != ']')
  {
    *tmp = *ptr;
    tmp++;
    ptr++;
  }
}

int main(int argc, char **argv)
{
  FILE *fp;
  char *input;
  char data[128];
  u32 sum = 0;
  char name[128];
  u32 sector = 0;
  char checksum[6];
  char cs[6];

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

  while(fscanf(fp, "%s ", data)!=EOF)
  {
    printf("%s\n", data);
    memset(name, 0, 128);
    memset(checksum, 0, 6);
    memset(cs, 0, 6);
    sector = 0;
    parse_room(data, name, &sector, checksum);
    printf("%s %d %s\n", name, sector, checksum);
    
    check_sum(name, cs);

    if (strcmp(cs, checksum) == 0)
    {
      sum += sector;
    }
  }

  printf("sum of sector ID %d.\n", sum);

  fclose(fp);
  return 0;
}
