#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int id;
  int from, to;
  bool used;
  Edge(int id, int from, int to) : id(id), from(from), to(to), used(false) {}
  bool operator<(const Edge& that) const {
    return id < that.id;
  };
};

vector<Edge> g[45];
vector<int> output;
vector<int> stack;
int start;
bool used[2000];
bool visit[45];

void euler(int node) {
  visit[node] = true;
  for (int i = 0; i < g[node].size(); i++) {
    if (used[g[node][i].id]) continue;
    used[g[node][i].id] = true;
    stack.push_back(g[node][i].id);
    euler(g[node][i].to);
  }
  if (!stack.empty()) {
    output.push_back(stack.back());
    stack.pop_back();
  }
}

int main() {
  int x, y, z;
  while (true) {
    for (int i = 1; i <= 44; i++)
      g[i].clear();
    bool has_input = false;
    while (cin >> x >> y) {
      if (x == 0 && y == 0) break;
      if (!has_input) {
        start = min(x, y);
        has_input = true;
      }
      cin >> z;
      g[x].push_back(Edge(z, x, y));
      g[y].push_back(Edge(z, y, x));
    }
    if (!has_input) break;
    bool odd = false;
    for (int i = 1; i <= 44; i++) {
      if (g[i].size() % 2 != 0) {
        odd = true;
        break;
      }
    }
    if (odd) {
      cout << "Round trip does not exist." << endl;
      continue;
    }
    memset(used, 0, sizeof(used));
    memset(visit, 0, sizeof(visit));
    output.clear();
    stack.clear();
    for (int i = 1; i <= 44; i++)
      sort(g[i].begin(), g[i].end());
    euler(start);
    bool connected = true;
    for (int i = 1; i <= 44; i++) {
      if (g[i].size() > 0 && !visit[i]) {
        connected = false;
        break;
      }
    }
    if (!connected) {
      cout << "Round trip does not exist." << endl;
      continue;
    }
    for (int i = output.size() - 1; i > 0; i--)
      cout << output[i] << ' ';
    cout << output[0] << endl;
  }
  return 0;
}
