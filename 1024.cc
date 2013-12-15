#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Wall {
  int x, y;
  bool left;
};

int w, h, m;
string way;
int best[100][100];
Wall wall[20000];
bool map[100][100][2];  // 0: left, 1: up
bool many[100][100]; // if there are many shortest paths
int dis[100][100];

void draw_best(string& way) {
  int x = 0, y = 0;
  memset(best, 0, sizeof(best));
  best[0][0] = 0;
  for (int i = 0; i < way.size(); i++) {
    if (way[i] == 'R' || way[i] == 'L') {
      x += way[i] == 'R' ? 1 : -1;
    } else {
      y += way[i] == 'U' ? 1 : -1;
    }
    best[x][y] = i + 1;
  }
}

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

bool check() {
  for (int i = 0; i < w; i++)
    for (int j = 0; j < h; j++)
      dis[i][j] = -1;
  memset(many, 0, sizeof(many));
  vector<pair<int, int> > q;
  dis[0][0] = 0;
  q.push_back(make_pair(0, 0));
  int head = 0;
  while (head < q.size()) {
    int x = q[head].first, y = q[head].second;
    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx == w || ny < 0 || ny == h) continue;
      // Check wall.
      if (i < 2) {
        if (map[x][y][i]) continue;
      } else {
        if (map[nx][ny][i % 2]) continue;
      }
      if (dis[nx][ny] == -1) {
        dis[nx][ny] = dis[x][y] + 1;
        many[nx][ny] = many[x][y];
        if (best[nx][ny] > 0 && (best[nx][ny] < dis[nx][ny] || many[nx][ny]))
          return false;  // first is also shortest.
        q.push_back(make_pair(nx, ny));
      } else if (dis[x][y] + 1 == dis[nx][ny]) {
          many[nx][ny] = true;
          if (best[nx][ny] > 0)
            return false;  // multiple paths.
      }
    }
    head++;
  }
  int x = 0, y = 0;
  for (int i = 0; i < way.size(); i++) {
    if (way[i] == 'R' || way[i] == 'L') {
      x += way[i] == 'R' ? 1 : -1;
    } else {
      y += way[i] == 'U' ? 1 : -1;
    }
    if (dis[x][y] == -1) return false;
  }
  return true;
}

bool judge() {
  if (!check()) return false;
  for (int i = 0; i < m; i++) {
    if (wall[i].left)
      map[wall[i].x][wall[i].y][0] = false;
    else
      map[wall[i].x][wall[i].y][1] = false;
    if (check()) return false;
    if (wall[i].left)
      map[wall[i].x][wall[i].y][0] = true;
    else
      map[wall[i].x][wall[i].y][1] = true;
  }
  return true;
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> w >> h;
    cin >> way;
    draw_best(way);
    cin >> m;
    memset(map, 0, sizeof(map));
    for (int i = 0; i < m; i++) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      if (x1 == x2) {
        wall[i].x = x1;
        wall[i].y = min(y1, y2);
        wall[i].left = false;
        map[wall[i].x][wall[i].y][1] = true;
      } else {
        wall[i].x = min(x1, x2);
        wall[i].y = y1;
        wall[i].left = true;
        map[wall[i].x][wall[i].y][0] = true;
      }
    }
    cout << (judge() ? "CORRECT" : "INCORRECT") << endl;
  }
  return 0;
}
