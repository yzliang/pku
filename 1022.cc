#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int n;
int x[101][4][2];

bool check_symmetry() {
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 4; j++) {
      if (x[i][j][0] != 0 && x[x[i][j][0]][j][1] != i)
        return false;
      if (x[i][j][1] != 0 && x[x[i][j][1]][j][0] != i)
        return false;
    }
  }
  return true;
}

struct State {
  int id;
  int x[4];
};

int compute() {
  int min_x[4] = {0};
  int max_x[4] = {0};
  bool go[101] = {0};
  go[0] = true;
  State s, ns;
  s.id = 1;
  memset(s.x, 0, sizeof(s.x));
  vector<State> q;
  q.push_back(s);
  int head = 0;
  while (head < q.size()) {
    s = q[head];
    for (int i = 0; i < 4; i++) {
      min_x[i] = min(min_x[i], s.x[i]);
      max_x[i] = max(max_x[i], s.x[i]);
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 2; j++) {
        if (x[s.id][i][j] == 0 || go[x[s.id][i][j]]) continue;
        ns.id = x[s.id][i][j];
        go[ns.id] = true;
        memcpy(ns.x, s.x, sizeof(ns.x));
        ns.x[i] = s.x[i] + (j == 0 ? -1 : 1);
        q.push_back(ns);
      }
    }
    head++;
  }
  if (q.size() < n) return -1;
  int ans = 1;
  for (int i = 0; i < 4; i++)
    ans *= max_x[i] - min_x[i] + 1;
  return ans;
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> n;
    map<int, int> id_map;
    for (int i = 1; i <= n; i++) {
      int id;
      cin >> id;
      for (int j = 0; j < 4; j++)
        cin >> x[i][j][0] >> x[i][j][1];
      id_map[id] = i;
    }
    // map id to array index.
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < 4; j++) {
        if (x[i][j][0] != 0)
          x[i][j][0] = id_map[x[i][j][0]];
        if (x[i][j][1] != 0)
          x[i][j][1] = id_map[x[i][j][1]];
      }
    }
    if (!check_symmetry()) {
      cout << "Inconsistent" << endl;
      continue;
    }
    int ans = compute();
    if (ans == -1)
      cout << "Inconsistent" << endl;
    else
      cout << ans << endl;
  }
  return 0;
}
