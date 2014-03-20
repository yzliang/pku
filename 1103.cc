#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int dx[] = {1, 1, -1, -1};
const int dy[2][4] = {
  {1, 0, 0, 1},
  {0, -1, -1, 0}
};

struct Cell {
  int x, y;
  Cell(int x, int y) : x(x), y(y) {}
};

int w, h, m, n, ans, total;
bool block[151][76][4];
bool visit[151][76];

inline bool in_bound(int x, int y) {
  if (x < 0 || x >= n)
    return false;
  if (x % 2 == 0)
    return y >= 0 && y < w;
  else
    return y >= 0 && y < w + 1;
}

void bfs(int sx, int sy) {
  bool cycle = true;
  queue<Cell> q;
  q.push(Cell(sx, sy));
  int size = 1;
  visit[sx][sy] = true;
  while (!q.empty()) {
    Cell head = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      if (block[head.x][head.y][i]) continue;
      int nx = head.x + dx[i];
      int ny = head.y + dy[head.x % 2][i];
      if (!in_bound(nx, ny)) {
        cycle = false;
        continue;
      }
      if (visit[nx][ny]) continue;
      visit[nx][ny] = true;
      size++;
      q.push(Cell(nx, ny));
    }
  }
  if (cycle) {
    total++;
    if (size > ans) ans = size;
  }
}

int main() {
  int id = 1;
  while (cin >> w >> h) {
    if (w == 0 && h == 0)
      break;
    n = 2 * h + 1;
    m = w + 1;
    // Load map.
    memset(block, 0, sizeof(block));
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        char c;
        cin >> c;
        if (c == '/') {
          block[2 * i][j][0] = block[2 * i + 1][j][0] = true;
          block[2 * i + 1][j + 1][2] = block[2 * i + 2][j][2] = true;
        } else {
          block[2 * i][j][1] = block[2 * i + 1][j + 1][1] = true;
          block[2 * i + 1][j][3] = block[2 * i + 2][j][3] = true;
        }
      }
    }
    // BFS.
    ans = 0;
    total = 0;
    memset(visit, 0, sizeof(visit));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (visit[i][j]) continue;
        bfs(i, j);
      }
    }
    cout << "Maze #" << id++ << ':' << endl;
    if (total > 0)
      cout << total << " Cycles; the longest has length " << ans << '.' << endl;
    else
      cout << "There are no cycles." << endl;
    cout << endl;
  }
  return 0;
}
