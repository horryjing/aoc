#include "stdio.h"
#include "string.h"
#include <openssl/md5.h>

int main(int argc, char **argv)
{
  MD5_CTX ctx;
  char input[128];
  unsigned char hash[MD5_DIGEST_LENGTH];
  int i=0, j=0;
  char *door_id;
  int pass_num = 0;
  unsigned char pwd[8] = "????????";

  if (argc != 2)
  {
    printf("invalid input.\n");
    return 0;
  }

  door_id = argv[1];

  while (pass_num < 8)
  {
    snprintf(input, 128, "%s%d", door_id, i++);

    MD5_Init(&ctx);
    MD5_Update(&ctx, input, strlen(input));
    MD5_Final(hash, &ctx);

    if ((hash[0] == 0)
        && (hash[1] == 0)
        && ((hash[2]>>4) == 0)
        && (hash[2] < 8)
        && (pwd[hash[2]] == '?'))
    {
      pwd[hash[2]] = hash[3]>>4;
      pass_num++;
    }
  }

  printf("password is: ");
  for (j=0; j<8; j++)
  {
    printf("%x", pwd[j]);
  }
  printf("\n");
  
  return 0;
}
