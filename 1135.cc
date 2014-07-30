#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int n, m;
int g[501][501];
int dis[501];
bool visit[501];

int main() {
  int id = 1;
  while (cin >> n >> m) {
    if (n == 0 && m == 0)
      break;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        g[i][j] = -1;
    for (int i = 0; i < m; i++) {
      int x, y, len;
      cin >> x >> y >> len;
      g[y][x] = g[x][y] = len;
    }
    // Dijkstra.
    for (int i = 1; i <= n; i++) {
      dis[i] = INT_MAX;
      visit[i] = false;
    }
    dis[1] = 0;
    for (int i = 1; i <= n; i++) {
      int k = -1;
      for (int j = 1; j <= n; j++) {
        if (!visit[j] && (k == -1 || dis[j] < dis[k]))
          k = j;
      }
      visit[k] = true;
      for (int j = 1; j <= n; j++) {
        if (!visit[j] && g[k][j] != -1 && dis[k] + g[k][j] < dis[j])
          dis[j] = dis[k] + g[k][j];
      }
    }
    // Find the last one.
    double last = -1;
    int a = -1, b = -1;
    for (int i = 1; i <= n; i++) {
      if (dis[i] > last) {
        last = dis[i];
        a = i;
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if (g[i][j] != -1 && abs(dis[i] - dis[j]) != g[i][j]) {
          double x = (g[i][j] + dis[j] - dis[i]) / 2.0;
          if (dis[i] + x > last) {
            last = dis[i] + x;
            a = i;
            b = j;
          }
        }
      }
    }
    cout << "System #" << id++ << endl;
    cout << "The last domino falls after ";
    cout << fixed << setprecision(1) << last << " seconds, ";
    if (b == -1)
      cout << "at key domino " << a;
    else
      cout << "between key dominoes " << a << " and " << b;
    cout << '.' << endl;
    cout << endl;
  }
  return 0;
}
