// 2009-03-06 20:34:19
#include <iostream>
using namespace std;

struct Point
{
  int x, y;
};

int n, base;
Point p[700];

bool ReadData()
{
  cin >> n;
  if (n == 0)
    return false;
  else
  {
    for (int i = 0; i < n; i++)
      cin >> p[i].x >> p[i].y;
    return true;
  }
}

int Multi(Point *p1, Point *p2, Point *p0)
{
  return (p1->x - p0->x) * (p2->y - p0->y) - (p2->x - p0->x) * (p1->y - p0->y);
}

int mycompare(const void *e1, const void *e2)
{
  return Multi((Point *)e1, (Point *)e2, &p[base]);
}

void Process()
{
  int ans = 1;
  Point tp[700];
  int i, j, tot;

  for (base = 0; base < n; base++)
  {
    tot = 0;
    for (i = 0; i < n; i++)
      if (p[i].y >= p[base].y && i != base)
        tp[tot++] = p[i];
    qsort(tp, tot, sizeof(Point), mycompare);
    i = 0;
    while (i < tot)
    {
      j = i + 1;
      while (j < tot && Multi(&tp[i], &tp[j], &p[base]) == 0)
        j++;
      if (j - i + 1 > ans)
        ans = j - i + 1;
      i = j;
    }
  }
  cout << ans << endl;
}

int main()
{
  while (ReadData())
    Process();
  return 0;
}
