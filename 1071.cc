#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Chase {
  int l1, l2;
  char c;
  Chase(int l1, int l2, char c): l1(l1), l2(l2), c(c) {}
};

struct Point {
  int x, y;
  Point() {}
  Point(int x, int y): x(x), y(y) {}
};

int n, m;
int map[100][100];
bool f[100][100], g[100][100];
vector<Chase> chases;
vector<Point> seeds;
int dx, dy;

void init(char c) {
  seeds.clear();
  switch (c) {
    case 'R':
      dx = 0;
      dy = 1;
      for (int i = 0; i < n; i++)
        seeds.push_back(Point(i, m - 1));
      break;
    case 'L':
      dx = 0;
      dy = -1;
      for (int i = 0; i < n; i++)
        seeds.push_back(Point(i, 0));
      break;
    case 'U':
      dx = -1;
      dy = 0;
      for (int i = 0; i < m; i++)
        seeds.push_back(Point(0, i));
      break;
    case 'D':
      dx = 1;
      dy = 0;
      for (int i = 0; i < m; i++)
        seeds.push_back(Point(n - 1, i));
      break;
  }
}

inline bool in_bound(const Point& p) {
  return p.x >= 0 && p.x < n && p.y >= 0 && p.y < m;
}

inline int dis(const Point& p1, const Point& p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> map[i][j];
        f[i][j] = map[i][j] == 0;
      }
    }
    chases.clear();
    while (true) {
      int l1, l2;
      cin >> l1 >> l2;
      if (l1 == 0 && l2 == 0) break;
      char c;
      cin >> c;
      chases.push_back(Chase(l1, l2, c));
    }
    for (int i = chases.size() - 1; i >= 0; i--) {
      init(chases[i].c);
      memset(g, false, sizeof(g));
      for (int j = 0; j < seeds.size(); j++) {
        Point current = seeds[j];
        Point q[100];
        int head = 0, tail = 0, count = 0;
        Point block(-1, -1);
        while (in_bound(current)) {
          // Pop.
          while (head < tail && dis(q[head], current) > chases[i].l2) {
            count -= f[q[head].x][q[head].y];
            head++;
          }
          // Insert.
          Point np(current.x + dx * chases[i].l1,
              current.y + dy * chases[i].l1);
          if (in_bound(np) && (block.x == -1 ||
                dis(block, current) > dis(np, current))) {
            q[tail++] = np;
            count += f[np.x][np.y];
          }
          if (map[current.x][current.y] == 0)
            g[current.x][current.y] = count > 0;
          else {
            head = tail = count = 0;
            block = current;
          }
          current.x -= dx;
          current.y -= dy;
        }
      }
      memcpy(f, g, sizeof(f));
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        ans += f[i][j];
    cout << ans << endl;
  }
  return 0;
}
