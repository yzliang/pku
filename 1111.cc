#include <cstring>
#include <iostream>
using namespace std;

struct Cell {
  int x, y;
};

const int dx[] = {0, 1, 0, -1, -1, 1, 1, -1};
const int dy[] = {1, 0, -1, 0, 1, 1, -1, -1};

int r, c;
char map[20][25];
bool visit[20][20];
Cell q[1000];

bool in_bound(int x, int y) {
  return x >= 0 && x < r && y >= 0 && y < c;
}

int main() {
  while (cin >> r >> c >> q[0].x >> q[0].y) {
    if (r == 0) break;
    for (int i = 0; i < r; i++)
      cin >> map[i];
    int head = 0, tail = 0;
    q[0].x--;
    q[0].y--;
    memset(visit, 0, sizeof(visit));
    visit[q[0].x][q[0].y] = true;
    while (head <= tail) {
      for (int i = 0; i < 8; i++) {
        int nx = q[head].x + dx[i], ny = q[head].y + dy[i];
        if (!in_bound(nx, ny) || visit[nx][ny] || map[nx][ny] == '.')
          continue;
        visit[nx][ny] = true;
        ++tail;
        q[tail].x = nx;
        q[tail].y = ny;
      }
      head++;
    }
    int ans = 0;
    for (int i = 0; i <= tail; i++) {
      for (int j = 0; j < 4; j++) {
        int nx = q[i].x + dx[j], ny = q[i].y + dy[j];
        if (!in_bound(nx, ny) || map[nx][ny] == '.')
          ans++;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
