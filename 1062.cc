// 2008-12-11 00:10:13
#include <iostream>
using namespace std;

struct goods
{
  int price;
  int level;
  int tot;
  int subgoods[100];
  int offprice[100];
};

int n, m, maxlevel;
goods g[101];

void ReadData()
{
  int i, j, tot, sub, off;
  cin >> m >> n;
  maxlevel = 0;
  for (i = 1; i <= n; i++)
    g[i].tot = 0;
  for (i = 1; i <= n; i++)
  {
    cin >> g[i].price >> g[i].level >> tot;
    if (g[i].level > maxlevel)
      maxlevel = g[i].level;
    for (j = 0; j < tot; j++)
    {
      cin >> sub >> off;
      g[sub].subgoods[g[sub].tot] = i;
      g[sub].offprice[g[sub].tot] = off;
      g[sub].tot++;
    }
  }
  /*g[0].price = 0;
  g[0].level = g[1].level;
  g[0].tot = n;
  for (i = 0; i < n; i++)
  { 
    g[0].subgoods[i] = i + 1;
    g[0].offprice[i] = g[i + 1].price;
  }*/
}

void Process()
{
  int price[101];
  int answer = g[1].price;
  int i, j, k;
  bool used[101];
  while (maxlevel >= g[1].level)
  {
    if (maxlevel - g[1].level > m)
    {
      maxlevel--;
      continue;
    }
    for (i = 1; i <= n; i++)
    {
      price[i] = g[i].price;
      used[i] = false;
    }
    for (i = 0; i < n; i++)
    {
      k = -1;
      for (j = 1; j <= n; j++)
        if (g[j].level <= maxlevel && maxlevel - g[j].level <= m && !used[j]
          && (k == -1 || price[j] < price[k]))
          k = j;
      if (k == -1)
        break;
      used[k] = true;
      for (j = 0; j < g[k].tot; j++)
        if (price[k] + g[k].offprice[j] < price[g[k].subgoods[j]])
          price[g[k].subgoods[j]] = price[k] + g[k].offprice[j];
    }
    if (price[1] < answer)
      answer = price[1];
    maxlevel--;
  }
  cout << answer << endl;
}

int main()
{
  ReadData();
  Process();
  return 0;
}
