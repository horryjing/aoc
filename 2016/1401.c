#include "stdio.h"
#include "string.h"
#include "openssl/md5.h"

#define BUF_SIZE 1024
#define NUM_KEYS 64
#define WINDOW 1000

char has_triple(unsigned char *h);
int has_quint(unsigned char *h, char m);

int main(int argc, char **argv)
{
  MD5_CTX  ctx;
  char *salt;
  char buffer[BUF_SIZE];
  unsigned char hash[MD5_DIGEST_LENGTH];
  char m;
  int i=0;
  int j=0;
  int key=0;

  if (argc != 2)
  {
    printf("input error.\n");
    return 0;
  }

  salt = argv[1];

  while (key < NUM_KEYS)
  {
    snprintf(buffer, BUF_SIZE, "%s%d", salt, i);
    MD5_Init(&ctx);
    MD5_Update(&ctx, buffer, strlen(buffer));
    MD5_Final(hash, &ctx);

    if ((m=has_triple(hash)) != -1)
    {
      for (j=i+1; j<i+WINDOW; j++)
      {
        snprintf(buffer, BUF_SIZE, "%s%d", salt, j);
        MD5_Init(&ctx);
        MD5_Update(&ctx, buffer, strlen(buffer));
        MD5_Final(hash, &ctx);
        if (has_quint(hash, m) == 1)
        {
          key++;
          break;
        }
      }
    }
    i++;
  }

  printf("index %d.\n", i-1);

  return 0;
}

char has_triple(unsigned char *h)
{
  int i;
  char m, c1, c2, c3;

  for (i=0; i<MD5_DIGEST_LENGTH-1; i++)
  {
    m = (h[i] & 0xF0) >> 4;
    c1 = h[i] & 0xF;
    c2 = (h[i+1] & 0xF0) >> 4;
    c3 = h[i+1] & 0xF;
    if (c1 == m && c2 == m)
    {
      return m;
    }
    m = c1;
    if (c2 == m && c3 ==m)
    {
      return m;
    }
  }

  return -1;
}

int has_quint(unsigned char *h, char m)
{
  int i;
  char c1, c2, c3, c4, c5, c6;

  for (i=0; i<MD5_DIGEST_LENGTH-2; i++)
  {
    c1 = (h[i] & 0xF0) >> 4;
    c2 = h[i] & 0xF;
    c3 = (h[i+1] & 0xF0) >> 4;
    c4 = h[i+1] & 0xF;
    c5 = (h[i+2] & 0xF0) >> 4;
    c6 = h[i+2] & 0xF;

    if (c2==m && c3==m && c4==m && c5==m && (c1==m || c6==m))
    {
      return 1;
    }
  }

  return 0;
}
