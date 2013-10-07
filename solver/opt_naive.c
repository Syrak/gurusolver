#include <stdio.h>
#include "target.h"
#include "opt_naive.h"

Target *buff[BUFF_SIZE];

num gtime_buff;

void naive_det_(Target**, int, const int);

num naive_det(Target** t, const int n)
{
  gtime_buff = 1./0.;

  naive_det_(t, 0, n);

  int i;

  for (i = 0 ; i < n ; i++)
  {
    t[i] = buff[i];
  }

  return gtime_buff;
}

void naive_det_(Target** t, int i, const int n)
{
  if (i == n)
  {
    num gtime = guru_time(t, n);
    
    if (gtime < gtime_buff)
    {
      gtime_buff = gtime;

      int j;

      for (j = 0 ; j < n ; j++)
      {
        buff[j] = t[j];
      }
    }

    return;
  }

  int j;
  Target *tgt = t[i];

  naive_det_(t, i+1, n);

  for (j = i+1 ; j < n ; j++)
  {
    t[j-1] = t[i];
    t[i] = t[j];
    t[j] = tgt;

    naive_det_(t, i+1, n);
  }

  t[n-1] = t[i];
  t[i] = tgt;
}

// Quick hack
void search(Target** t, const int n, Target* tgt, int field, num min, num max, num tolerance)
{
  while (max-min > tolerance)
  {
    num mid = (max + min) / 2;

    switch (field)
    {
      case 0:
        tgt->p = mid;
        break;
      case 1:
        tgt->e = mid;
        break;
      default:
        tgt->w = mid;
    }

    naive_det(t, n);

    switch (field)
    {
      case 0:
      case 1:
        if (t[0] == tgt)
          max = mid;
        else
          min = mid;
        break;
      default:
        if (t[0] == tgt)
          min = mid;
        else
          max = mid;
    }
  }
}
