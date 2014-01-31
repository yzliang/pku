#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int n, sink;
vector<char> types;
vector<string> args;
string ids[20];
string names[20];
bool g[50][50], can[50][50];
int ans[20];

void read_input() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> ids[i];
  char c;
  string s;
  set<string> name_set;
  while (cin >> c) {
    if (c == 'Q') break;
    cin >> s;
    types.push_back(c);
    args.push_back(s);
    if (c != 'M')
      name_set.insert(s);
  }
  int i = 0;
  for (set<string>::iterator j = name_set.begin(); j != name_set.end(); j++)
    names[i++] = *j;
  sort(names, names + n);
}

void build_graph() {
  // 0: source, 1~n: names, n+1~2n: ids, 2n+1: sink
  sink = 2 * n + 1;
  for (int i = 1; i <= n; i++)
    g[0][i] = true;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      g[i][n + j] = true;
  for (int i = 1; i <= n; i++)
    g[n + i][2 * n + 1] = true;
  int name_set = 0;
  for (int i = 0; i < types.size(); i++) {
    if (types[i] == 'M') {
      int id = 0;
      while (ids[id] != args[i]) id++;
      for (int j = 0; j < n; j++) {
        if (!(name_set & (1 << j)))
          g[j + 1][id + n + 1] = false;
      }
    } else {
      int name = 0;
      while (names[name] != args[i]) name++;
      if (types[i] == 'E')
        name_set |= (1 << name);
      else
        name_set &= ~(1 << name);
    }
  }
}

int max_flow() {
  int total = 0;
  int head, tail;
  int q[50], pre[50];
  while (true) {
    bool go[50] = {0};
    go[0] = true;
    q[0] = 0;
    head = 0;
    tail = 1;
    while (head < tail && !go[sink]) {
      for (int i = 1; i <= sink; i++) {
        if (!go[i] && can[q[head]][i]) {
          go[i] = true;
          pre[i] = q[head];
          q[tail++] = i;
          if (i == sink) break;
        }
      }
      head++;
    }
    if (!go[sink]) break;
    total++;
    int node = sink;
    while (node != 0) {
      int prev = pre[node];
      can[prev][node] = false;
      can[node][prev] = true;
      node = prev;
    }
  }
  return total;
}

void get_mapping(int* mapping) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (g[i + 1][j + n + 1] && !can[i + 1][j + n + 1])
        mapping[i] = j;
}

void infer() {
  memcpy(can, g, sizeof(can));
  max_flow();
  get_mapping(ans);
  // Check uniqueness.
  for (int i = 0; i < n; i++) {
    memcpy(can, g, sizeof(can));
    can[i + 1][ans[i] + n + 1] = false;
    if (max_flow() == n)
      ans[i] = -1;
  }
}

int main() {
  read_input();
  build_graph();
  infer();
  for (int i = 0; i < n; i++) {
    cout << names[i] << ':';
    cout << (ans[i] == -1 ? "???" : ids[ans[i]]) << endl;
  }
  return 0;
}
