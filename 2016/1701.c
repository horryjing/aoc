#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "openssl/md5.h"

#define BUF_SIZE 16384

typedef struct path_t
{
  char path[BUF_SIZE];
  int length;
  int r;
  int c;
  struct path_t *next;
}path;

path *queue = NULL;
path *shortest = NULL;
path *longest = NULL;

path *create(char *p, int r, int c);
path *gen(char *pass);

int main(int argc, char **argv)
{
  char *pwd = NULL;
  
  if (argc != 2)
  {
    printf("invalid input\n");
    return 0;
  }

  pwd = argv[1];

  queue = create("", 0, 0);
  while (queue != NULL)
  {
    queue = gen(pwd);
  }

    printf("The shortest path to the vault is %s.\n", shortest->path);
    printf("It is %d steps long.\n", shortest->length);
    printf("The longest path to the vault is %s.\n", longest->path);
    printf("It is %d steps long.\n", longest->length);
    free(shortest);
    free(longest);
    return 0;
}

path *create(char *p, int r, int c)
{
  path *new = (path *)malloc(sizeof(path));

  strcpy(new->path, p);
  new->length = strlen(p);
  new->r = r;
  new->c = c;
  new->next = NULL;

  return new;
}

path *gen(char *pwd)
{
  MD5_CTX ctx;
  unsigned char hash[MD5_DIGEST_LENGTH];
  int u, d, l, r;
  path *cur = queue;
  char buffer[BUF_SIZE] = {0};
  path *tmp = NULL;
  path *new_queue = NULL;

  while (cur != NULL)
  {
    if (cur->r == 3 && cur->c == 3)
    {
      if (shortest == NULL)
      {
        shortest  = cur;
      }
      if (longest != shortest && longest != NULL)
      {
        free(longest);
      }
      longest = cur;
    }
    else
    {
      strcpy(buffer, pwd);
      strcat(buffer, cur->path);
      MD5_Init(&ctx);
      MD5_Update(&ctx, buffer, strlen(buffer));
      MD5_Final(hash, &ctx);

      u = (hash[0] & 0xF0) >> 4;
      d = hash[0] & 0xF;
      l = (hash[1] & 0xF0) >> 4;
      r = hash[1] &0xF;

      if (u>=0xb && cur->r > 0)
      {
        strcpy(buffer, cur->path);
        strcat(buffer, "U");
        tmp = create(buffer, cur->r-1, cur->c);
        if (new_queue == NULL)
        {
          new_queue = tmp;
        }
        else
        {
          tmp->next = new_queue;
          new_queue = tmp;
        }
      }

      if (d>=0xb && cur->r < 3)
      {
        strcpy(buffer, cur->path);
        strcat(buffer, "D");
        tmp = create(buffer, cur->r+1, cur->c);
        if (new_queue == NULL)
        {
          new_queue = tmp;
        }
        else
        {
          tmp->next = new_queue;
          new_queue = tmp;
        }
      }

      if (l>=0xb && cur->c>0)
      {
        strcpy(buffer, cur->path);
        strcat(buffer, "L");
        tmp = create(buffer, cur->r, cur->c-1);
        if (new_queue == NULL)
        {
          new_queue = tmp;
        }
        else
        {
          tmp->next = new_queue;
          new_queue = tmp;
        }
      }

      if (r>=0xb && cur->c<3)
      {
        strcpy(buffer, cur->path);
        strcat(buffer, "R");
        tmp = create(buffer, cur->r, cur->c+1);
        if (new_queue == NULL)
        {
          new_queue = tmp;
        }
        else
        {
          tmp->next = new_queue;
          new_queue = tmp;
        }
      }
    }
    tmp = cur;
    cur = cur->next;
    if (tmp!=shortest && tmp!=longest)
    {
      free(tmp);
    }
  }
  return new_queue;
}
