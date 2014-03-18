#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Point {
  int x, y;
} v[200];

int cross_product(Point& p1, Point& p2, Point& p3, Point& p4) {
  return (p2.x - p1.x) * (p4.y - p3.y) - (p4.x - p3.x) * (p2.y - p1.y);
}

struct Comparator {
  int i;
  Comparator(int i) : i(i) {}
  bool operator()(int p, int q) {
    bool up1 = v[p].y > v[i].y;
    bool up2 = v[q].y > v[i].y;
    if (up1 ^ up2) {
      return up2;
    } else {
      if (v[p].y == v[i].y && v[q].y == v[i].y)
        return v[p].x < v[i].x;
      else
        return cross_product(v[i], v[p], v[i], v[q]) > 0;
    }
  }
};

map<int, int> id_to_index;
int n, size, ans;
int id[200], deg[200];
int adj[200][200];
bool marked[200][200][2];
bool full;

double mod(Point& p1, Point& p2) {
  return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double corner_angle(int i, int j, int k) {
  double mod1 = mod(v[i], v[j]), mod2 = mod(v[j], v[k]);
  double val = cross_product(v[i], v[j], v[j], v[k]) / mod1 / mod2;
  if (val > 1)
    val = 1;
  if (val < -1)
    val = -1;
  return asin(val);
}

void color(int s1, int s2, int d) {
  vector<int> path;
  path.push_back(s1);
  path.push_back(s2);
  int x = s1, y = s2;
  do {
    marked[x][y][d] = marked[y][x][1 - d] = true;
    for (int i = 0; i < deg[y]; i++) {
      if (adj[y][i] == x) {
        x = y;
        if (d == 0) {  // left.
          y = adj[y][(i + deg[y] - 1) % deg[y]];
        } else {  // right.
          y = adj[y][(i + 1) % deg[y]];
        }
        break;
      }
    }
    path.push_back(y);
  } while (x != s1 || y != s2);
  path.pop_back();
  path.pop_back();
  bool visit[200] = {0};
  bool valid = true;
  for (int i = 0; i < path.size(); i++) {
    if (visit[path[i]]) {
      valid = false;
      break;
    }
    visit[path[i]] = true;
  }
  // Check for outer face (the inner is nonempty).
  double angle = 0;
  for (int i = 0; i < path.size(); i++)
    angle += corner_angle(path[i], path[(i + 1) % path.size()],
        path[(i + 2) % path.size()]);
  // angle > 0 is counter-clockwise.
  if ((angle > 0 && d == 1) || (angle < 0 && d == 0))
    valid = false;
  if (valid && path.size() == size) {
    ans++;
  }
}

int main() {
  int m;
  cin >> m;
  for (; m > 0; m--) {
    cin >> n;
    id_to_index.clear();
    for (int i = 0; i < n; i++) {
      cin >> id[i] >> v[i].x >> v[i].y;
      id_to_index[id[i]] = i;
      cin >> deg[i];
      for (int j = 0; j < deg[i]; j++)
        cin >> adj[i][j];
    }
    cin >> size;
    // Convert ids to indices.
    for (int i = 0; i < n; i++)
      for (int j = 0; j < deg[i]; j++)
        adj[i][j] = id_to_index[adj[i][j]];
    // Sort edges counter-clockwisely.
    for (int i = 0; i < n; i++)
      sort(adj[i], adj[i] + deg[i], Comparator(i));
    // Coloring.
    memset(marked, 0, sizeof(marked));
    ans = 0;
    full = false;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < deg[i]; j++) {
        if (!marked[i][adj[i][j]][0])
          color(i, adj[i][j], 0);
        if (!marked[i][adj[i][j]][1])
          color(i, adj[i][j], 1);
      }
    }
    cout << ans << endl;
  }
  return 0;
}
