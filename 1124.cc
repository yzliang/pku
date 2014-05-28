#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
using namespace std;

struct Point {
  int x, y;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}
};

int r, c, sx, sy, tx, ty;
double factor;
char map[20][21];
int lx[26], ly[26];  // location of letters.
double load[20][20];
int dis[20][20], amount[20][20];
Point path[80];

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
const int BIG = 10000;

inline bool inbox(int x, int y) {
  return x >= 0 && x < r && y >= 0 && y < c;
}

void add_load(int x, int y, int top) {
  if (x == sx && y == sy) {
    for (int i = 0; i < top - 1; i++)
      load[path[i].x][path[i].y] += factor;
  }
  for (int i = 0; i < 4; i++) {
    int px = x + dx[i], py = y + dy[i];
    if (inbox(px, py) && dis[px][py] + 1 == dis[x][y]) {
      path[top].x = px;
      path[top].y = py;
      add_load(px, py, top + 1);
    }
  }
}

void process(char c1, char c2) {
  // BFS.
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      dis[i][j] = BIG;
  sx = lx[c1 - 'A'];
  sy = ly[c1 - 'A'];
  tx = lx[c2 - 'A'];
  ty = ly[c2 - 'A'];
  dis[sx][sy] = 0;
  memset(amount, 0, sizeof(amount));
  amount[sx][sy] = 1;
  queue<Point> q;
  q.push(Point(sx, sy));
  while (!q.empty()) {
    Point head = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int nx = head.x + dx[i], ny = head.y + dy[i];
      if (inbox(nx, ny) && map[nx][ny] == '.') {
        if (dis[head.x][head.y] + 1 < dis[nx][ny]) {
          dis[nx][ny] = dis[head.x][head.y] + 1;
          amount[nx][ny] = amount[head.x][head.y];
          q.push(Point(nx, ny));
        } else if (dis[head.x][head.y] + 1 == dis[nx][ny])
          amount[nx][ny] += amount[head.x][head.y];
      }
    }
  }
  // DFS.
  for (int i = 0; i < 4; i++) {
    int px = tx + dx[i], py = ty + dy[i];
    if (inbox(px, py)) {
      if (dis[px][py] + 1 < dis[tx][ty]) {
        dis[tx][ty] = dis[px][py] + 1;
        amount[tx][ty] = amount[px][py];
      } else if (dis[px][py] + 1 == dis[tx][ty])
        amount[tx][ty] += amount[px][py];
    }
  }
  factor /= amount[tx][ty];
  add_load(tx, ty, 0);
}

int main() {
  cin >> c >> r;
  for (int i = 0; i < r; i++) {
    cin >> map[i];
    for (int j = 0; j < c; j++) {
      if (map[i][j] != 'X' && map[i][j] != '.') {
        int k = map[i][j] - 'A';
        lx[k] = i;
        ly[k] = j;
      }
    }
  }
  char c1, c2;
  while (cin >> c1 >> c2 >> factor) {
    if (c1 == 'X' && c2 == 'X')
      break;
    process(c1, c2);
  }
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++)
      cout << setw(7) << fixed << setprecision(2) << load[i][j];
    cout << endl;
  }
  return 0;
}
