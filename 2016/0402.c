#include "stdio.h"
#include "string.h"

typedef unsigned int u32;

void parse_room(char *data, char *name, u32 *sector, char *checksum);
void check_sum(char *name, char *cs);
void get_room(char *data, char *name_en);
void decrypt_room(char *name_en, u32 sector, char *name_de);

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

void get_room(char *data, char *room_en)
{
  char *ptr;
  char *tmp;

  ptr = data;
  tmp = room_en;
  while (!((*ptr>='0') && (*ptr<='9')))
  {
    *tmp = *ptr;
    ptr++;
    tmp++;
  }

  tmp--;
  *tmp = '\0';
}

void decrypt_room(char *name_en, u32 sector, char *name_de)
{
  char *ptr;
  char *tmp;
  char i;

  ptr = name_en;
  tmp = name_de;

  while (*ptr != '\0')
  {
    if (*ptr == '-')
    {
      *tmp = *ptr;
    }
    else
    {
      i = *ptr - 'a';
      i = (i + sector) % 26;
      *tmp = i + 'a';
    }
    ptr++;
    tmp++;
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
  char room_en[128];
  char room_de[128];

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
    //printf("%s\n", data);
    memset(name, 0, 128);
    memset(checksum, 0, 6);
    memset(cs, 0, 6);
    memset(room_en, 0, 128);
    memset(room_de, 0, 128);
    sector = 0;
    parse_room(data, name, &sector, checksum);
    //printf("%s %d %s\n", name, sector, checksum);
    
    check_sum(name, cs);

    if (strcmp(cs, checksum) == 0)
    {
      sum += sector;
      get_room(data, room_en);
      //printf("%s\n", room_en);
      decrypt_room(room_en, sector, room_de);
      //printf("%s\n", room_de);
      if (strstr(room_de, "northpole") != NULL)
      {
        printf("%s %d.\n", room_de, sector);
        break;
      }
    }
  }

  //printf("sum of sector ID %d.\n", sum);

  fclose(fp);
  return 0;
}
