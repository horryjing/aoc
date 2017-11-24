#include "stdio.h"

#define WEAPONS_NUM 5
#define ARMORS_NUM 6
#define RINGS_NUM 7

typedef struct weapon_t
{
  int cost;
  int damage;
}weapon;

typedef struct armor_t
{
  int cost;
  int armor;
}armor;

typedef struct ring_t
{
  int cost;
  int damage;
  int armor;
}ring;

typedef struct person_t
{
  int point;
  int damage;
  int armor;
}person;

weapon w[WEAPONS_NUM];
armor a[ARMORS_NUM];
ring r[RINGS_NUM];
person p[2];

int win();
int equip(int w, int a, int r1, int r2);
int init();

int main(int argc, char **argv)
{
  int i, j, k, l;
  int cost = 0;
  int min = 1000;

  init();
  for (i=0; i<WEAPONS_NUM; i++)
  {
    for (j=0; j<ARMORS_NUM; j++)
    {
      for (k=0; k<RINGS_NUM; k++)
      {
        for (l=0; l<RINGS_NUM; l++)
        {
          if ((l!=0) && (k==l))
          {
            continue;
          }
          equip(i, j, k, l);
          if (win() == 1)
          {
            cost = w[i].cost + a[j].cost + r[k].cost + r[l].cost;
            printf("%d %d %d %d -> %d\n", i, j, k, l, cost);
            if (cost < min)
            {
              min = cost;
            }
          }
          init();
          cost = 0;
        }
      }
    }
  }
  printf("min %d\n", min);

  return 0;
}

int equip(int wn, int an, int rn1, int rn2)
{

  p[0].damage = w[wn].damage + r[rn1].damage + r[rn2].damage;
  p[0].armor = a[an].armor + r[rn1].armor + r[rn2].armor;
}

int win()
{
  while ((p[0].point >0) && (p[1].point > 0))
  {
    if (p[0].damage > p[1].armor)
    {
      p[1].point -= p[0].damage - p[1].armor;
    }
    else
    {
      p[1].point--;
    }
    if (p[1].damage > p[0].armor)
    {
      p[0].point -= p[1].damage - p[0].armor;
    }
    else
    {
      p[0].point--;
    }
  }
  if (p[1].point <= 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int init()
{
  w[0].cost = 8;
  w[0].damage = 4;
  w[1].cost = 10;
  w[1].damage = 5;
  w[2].cost = 25;
  w[2].damage = 6;
  w[3].cost = 40;
  w[3].damage = 7;
  w[4].cost = 74;
  w[4].damage = 8;
  a[0].cost = 0;
  a[0].armor = 0;
  a[1].cost = 13;
  a[1].armor = 1;
  a[2].cost = 31;
  a[2].armor = 2;
  a[3].cost = 53;
  a[3].armor = 3;
  a[4].cost = 75;
  a[4].armor = 4;
  a[5].cost = 102;
  a[5].armor = 5;
  r[0].cost = 0;
  r[0].damage = 0;
  r[0].armor = 0;
  r[1].cost = 25;
  r[1].damage = 1;
  r[1].armor = 0;
  r[2].cost = 50;
  r[2].damage = 2;
  r[2].armor = 0;
  r[3].cost = 100;
  r[3].damage = 3;
  r[3].armor = 0;
  r[4].cost = 20;
  r[4].damage = 0;
  r[4].armor = 1;
  r[5].cost = 40;
  r[5].damage = 0;
  r[5].armor = 2;
  r[6].cost = 80;
  r[6].damage = 0;
  r[6].armor = 3;
  p[0].point = 100;
  p[0].damage = 0;
  p[0].armor = 0;
  p[1].point = 104;
  p[1].damage = 8;
  p[1].armor = 1;
}
