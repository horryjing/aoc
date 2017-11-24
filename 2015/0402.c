#include "stdio.h"
#include "string.h"
#include "openssl/md5.h"

#define LEN 128


int main(int argc, char **argv)
{
  char *key = NULL;
  char input[LEN] = {0};
  unsigned char hash[MD5_DIGEST_LENGTH] = {0};
  int i = 0;
  MD5_CTX ctx;

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }
  key = argv[1];
  printf("key: %s\n", key);

  while (1)
  {
    sprintf(input, "%s%d", key, i);

    MD5_Init(&ctx);
    MD5_Update(&ctx, input, strlen(input));
    MD5_Final(hash, &ctx);

    if ((hash[0] == 0)
      &&(hash[1] == 0)
      &&(hash[2] == 0))
    {
      break;
    }
    i++;
  }

  printf("%d\n", i);

  return 0;
}
