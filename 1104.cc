#include <cstring>
#include <iostream>
using namespace std;

const int dx[] = {0, 0, 1, 0, -1};
const int dy[] = {0, 1, 0, -1, 0};

int w, h, t;
bool out[101][101][101], f[101][101][101], g[101][101][101];
int pos[101][2];

inline bool in_bound(int x, int y) {
  return x >= 1 && x <= w && y >= 1 && y <= h;
}

int main() {
  int id = 1;
  while (cin >> w >> h >> t) {
    if (w == 0) break;
    int n;
    cin >> n;
    memset(out, 0, sizeof(out));
    for (int i = 0; i < n; i++) {
      int x1, y1, x2, y2, ti;
      cin >> ti >> x1 >> y1 >> x2 >> y2;
      for (int x = x1; x <= x2; x++)
        for (int y = y1; y <= y2; y++)
          out[ti][x][y] = true;
    }
    // Forward inference.
    memset(f, 0, sizeof(f));
    for (int x = 1; x <= w; x++)
      for (int y = 1; y <= h; y++)
        f[1][x][y] = !out[1][x][y];
    for (int i = 1; i < t; i++) {
      for (int x = 1; x <= w; x++) {
        for (int y = 1; y <= h; y++) {
          if (!f[i][x][y]) continue;
          for (int j = 0; j < 5; j++) {
            int nx = x + dx[j], ny = y + dy[j];
            if (!in_bound(nx, ny) || out[i + 1][nx][ny]) continue;
            f[i + 1][nx][ny] = true;
          }
        }
      }
    }
    // Backward inference.
    memset(g, 0, sizeof(g));
    memcpy(g[t], f[t], sizeof(f[t]));
    for (int i = t; i > 1; i--) {
      for (int x = 1; x <= w; x++) {
        for (int y = 1; y <= h; y++) {
          if (!g[i][x][y]) continue;
          for (int j = 0; j < 5; j++) {
            int nx = x + dx[j], ny = y + dy[j];
            if (!in_bound(nx, ny) || out[i - 1][nx][ny]) continue;
            g[i - 1][nx][ny] = true;
          }
        }
      }
    }
    // Deduction.
    bool escaped = false;
    memset(pos, 0, sizeof(pos));
    for (int i = 1; i <= t; i++) {
      bool clear = true;
      for (int x = 1; x <= w; x++) {
        for (int y = 1; y <= h; y++) {
          if (!f[i][x][y] || !g[i][x][y]) continue;
          clear = false;
          if (pos[i][0] == 0) {
            pos[i][0] = x;
            pos[i][1] = y;
          } else {
            pos[i][0] = -1;
            break;
          }
        }
        if (pos[i][0] == -1) break;
      }
      if (clear) {
        escaped = true;
        break;
      }
    }
    cout << "Robbery #" << id++ << ':' << endl;
    if (escaped)
      cout << "The robber has escaped." << endl;
    else {
      bool known = false;
      for (int i = 1; i <= t; i++) {
        if (pos[i][0] == -1) continue;
        known = true;
        cout << "Time step " << i << ": The robber has been at " << pos[i][0]
             << ',' << pos[i][1] << '.' << endl;
      }
      if (!known)
        cout << "Nothing known." << endl;
    }
    cout << endl;
  }
  return 0;
}
