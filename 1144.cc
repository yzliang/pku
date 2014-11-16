#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int n;
bool g[100][100];
bool cut[100];
int dfn[100];  // dfs order id
int low[100];  // earliest dfn from current node
int next_id;

void dfs(int x, int parent) {
  dfn[x] = next_id++;
  low[x] = dfn[x];
  int num_children = 0;
  for (int i = 1; i <= n; i++) {
    if (!g[x][i] || i == parent) continue;
    if (dfn[i] == 0) {
      num_children++;
      dfs(i, x);
      low[x] = min(low[x], low[i]);
      if (parent != 0 && low[i] >= dfn[x])
        cut[x] = true;
    } else
      low[x] = min(low[x], dfn[i]);
  }
  if (parent == 0 && num_children > 1)
    cut[x] = true;  // root case
}

int main() {
  while (cin >> n) {
    if (n == 0) break;
    memset(g, 0, sizeof(g));
    // Parse input.
    int x;
    while (cin >> x) {
      if (x == 0) break;
      string line;
      getline(cin, line);
      istringstream iss(line);
      int y;
      while (iss >> y)
        g[x][y] = g[y][x] = true;
    }
    // DFS.
    memset(dfn, 0, sizeof(dfn));
    memset(cut, 0, sizeof(cut));
    next_id = 1;
    dfs(1, 0);
    // Output.
    cout << count(&cut[1], &cut[n + 1], true) << endl;
  }
  return 0;
}
