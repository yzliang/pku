#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Point {
  int x, y;
};

int n, m;
Point a[100], b[100];
vector<int> g[210];
bool can[210][210] = {0};

double dis(Point&p1, Point& p2) {
  double dx = p1.x - p2.x, dy = p1.y - p2.y;
  return sqrt(dx * dx + dy * dy);
}

bool can_visit(Point& p1, Point& p2, Point& p3) {
  return dis(p1, p3) + dis(p2, p3) <= 2 * dis(p1, p2);
}

void build_graph() {
  // source: 0
  // a[0..n-2]: 1, ..., n-1
  // b[0..m-1]: n, ..., n+m-1
  // sink: n+m
  for (int i = 1; i < n; i++) {
    g[0].push_back(i);
    can[0][i] = true;
  }
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < m; j++)
      if (can_visit(a[i], a[i + 1], b[j])) {
        g[i + 1].push_back(j + n);
        g[j + n].push_back(i + 1);
        can[i + 1][j + n] = true;
      }
  for (int i = 0; i <= m; i++) {
    g[i + n].push_back(n + m);
    can[i + n][n + m] = true;
  }
}

int max_flow() {
  int total = 0;
  while (true) {
    // find a path from source to sink.
    int pre[210] = {0};
    bool go[210] = {0};
    queue<int> q;
    q.push(0);
    go[0] = true;
    while (!q.empty() && !go[n + m]) {
      int head = q.front();
      q.pop();
      for (int i = 0; i < g[head].size(); i++) {
        if (go[g[head][i]] || !can[head][g[head][i]]) continue;
        go[g[head][i]] = true;
        pre[g[head][i]] = head;
        if (g[head][i] == n + m) break;
        q.push(g[head][i]);
      }
    }
    if (!go[n + m]) break;  // no more augmenting path.
    total++;
    int node = n + m;
    while (node != 0) {
      int prev = pre[node];
      can[prev][node] = false;
      can[node][prev] = true;
      node = prev;
    }
  }
  return total;
}

void output_path() {
  for (int i = 0; i < n - 1; i++) {
    cout << a[i].x << ' ' << a[i].y << ' ';
    for (int j = 0; j < m; j++) {
      if (can[n + j][i + 1]) {
        cout << b[j].x << ' ' << b[j].y << ' ';
        break;
      }
    }
  }
  cout << a[n - 1].x << ' ' << a[n - 1].y << endl;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> a[i].x >> a[i].y;
  for (int i = 0; i < m; i++)
    cin >> b[i].x >> b[i].y;
  build_graph();
  cout << max_flow() + n << endl;
  output_path();
  return 0;
}
