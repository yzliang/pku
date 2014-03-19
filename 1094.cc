// 2009-01-17 02:02:35
#include <iostream>
#include <list>
#include <queue>
#include <string>
using namespace std;

int n, m;
list<int> graph[26];
int deg[26];

bool TopSort(int step)
{
  queue<int> q;
  int d[26];
  int i;
  bool visit[26];
  bool determined = true;
  list<int>::const_iterator it;
  string order;

  memcpy(d, deg, sizeof(int) * n);
  for (i = 0; i < n; i++)
    if (d[i] == 0)
    {
      if (!q.empty())
        determined = false;
      q.push(i);
    }
  memset(visit, 0, sizeof(visit));
  order.clear();
  while (!q.empty())
  {
    i = q.front();
    visit[i] = true;
    order += (char)(i + 'A');
    for (it = graph[i].begin(); it != graph[i].end(); it++)
      {
        d[*it]--;
        if (d[*it] == 0)
          q.push(*it);
      }
    q.pop();
    if (q.size() > 1)
      determined = false;
  }
  if (order.length() < n)
  {
    cout << "Inconsistency found after " << step + 1 << " relations.\n";
    return true;
  }
  if (determined)
  {
    cout << "Sorted sequence determined after " << step + 1 << " relations: " << order << ".\n";
    return true;
  }
  return false;
}

void Process()
{
  int i, result;
  char c1, op, c2;

  memset(deg, 0, sizeof(deg));
  for (i = 0; i < n; i++)
    graph[i].clear();
  for (i = 0; i < m; i++)
  {
    cin >> c1 >> op >> c2;
    deg[c2 - 'A']++;
    graph[c1 - 'A'].push_back(c2 - 'A');
    if (TopSort(i))
    { 
      for (i++; i < m; i++)
        cin >> c1 >> op >> c2;
      return;
    }
  }
  cout << "Sorted sequence cannot be determined.\n";
}

int main()
{
  while (1)
  {
    cin >> n >> m;
    if (n == 0)
      break;
    Process();
  }
  return 0;
}
