#include "stdio.h"

enum addr
{
  A,B,C,D,E,F,G,H,MAX
};

int matrix[8][8] = 
{
    //       A,      B,      C,      D,      E,      F,      G,      H
    /* A*/  {0,      34,     100,    63,     108,    111,    89,     132},
    /* B*/  {34,     0,      4,      79,     44,     147,    133,    74},
    /* C*/  {100,    4,      0,      105,    95,     48,     88,     7},
    /* D*/  {63,     79,     105,    0,      68,     134,    107,    40},
    /* E*/  {108,    44,     95,     68,     0,      11,     66,     144},
    /* F*/  {111,    147,    48,     134,    11,     0,      115,    135},
    /* G*/  {89,     133,    88,     107,    66,     115,    0,      127},
    /* H*/  {132,    74,     7,      40,     144,    135,    127,    0}
};

int status = 0;

int dist[8][8] = 
{
//        A,      B,      C,      D,      E,      F,      G,      H
/*  A*/  {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000},
/*  B*/  {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000},
/*  C*/  {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000},
/*  D*/  {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000},
/*  E*/  {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000},
/*  F*/  {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000},
/*  G*/  {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000},
/*  H*/  {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000}
};

int main(int argc, char **argv)
{
  int a,b,c,d,e,f,g,h;
  int sum = 0;
  int min = 100000;

  for (a=0; a<8; a++)
  {
    for (b=0; b<8; b++)
    {
      if (b==a) continue;
      for (c=0; c<8; c++)
      {
        if (c==a || c==b) continue;
        for (d=0; d<8; d++)
        {
          if (d==a || d==b || d==c) continue;
          for (e=0; e<8; e++)
          {
            if (e==a || e==b || e==c || e==d) continue;
            for (f=0; f<8; f++)
            {
              if (f==a || f==b || f==c || f==d || f==e) continue;
              for (g=0; g<8; g++)
              {
                if (g==a || g==b || g==c || g==d || g==e || g==f) continue;
                for (h=0; h<8; h++)
                {
                  if (h==a || h==b || h==c || h==d || h==e || h==f || h==g) continue;
                  sum = 0;
                  sum += matrix[a][b] + matrix[b][c] + matrix[c][d] + matrix[d][e] + matrix[e][f] + matrix[f][g] + matrix[g][h];
                  if (sum < min) min=sum;
                  printf("%d %d %d %d %d %d %d %d sum %d\n", a, b, c, d, e, f, g, h, sum);
                }
              }
            }
          }
        }
      }
    }
  }
  printf("min %d\n", min);

  return 0;
}
