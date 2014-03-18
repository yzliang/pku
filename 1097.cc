#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct Sign {
  int s, t;
  double dis;
};

int n, m, k, s;
bool conn[30][30];
double dis[30][30];
int city[30];
string name[30];
Sign signs[1000];

const double INF = 1e10;
double f[30][30];
int g[30][30];

void floyd() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      f[i][j] = conn[i][j] ? dis[i][j] : INF;
      g[i][j] = -1;
    }
  }
  for (int l = 0; l < n; l++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (f[i][l] < INF && f[l][j] < INF && f[i][l] + f[l][j] < f[i][j]) {
          f[i][j] = f[i][l] + f[l][j];
          g[i][j] = l;
        }
      }
    }
  }
}

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  cin >> n >> m >> k;
  for (int i = 0; i < m; i++) {
    int x, y;
    double d;
    cin >> x >> y >> d;
    dis[x][y] = dis[y][x] = d;
    conn[x][y] = conn[y][x] = true;
  }
  for (int i = 0; i < k; i++)
    cin >> city[i] >> name[i];
  cin >> s;
  for (int i = 0; i < s; i++)
    cin >> signs[i].s >> signs[i].t >> signs[i].dis;
  floyd();
  for (int i = 0; i < s; i++) {
    // Find cities.
    int total = 0;
    int ids[30], dis[30];
    for (int j = 0; j < k; j++) {
      if (f[signs[i].s][city[j]] == INF || city[j] == signs[i].s)
        continue;  // Not connected or is the source.
      int mid = city[j];
      while (g[signs[i].s][mid] != -1)
        mid = g[signs[i].s][mid];
      if (mid != signs[i].t)
        continue;
      ids[total] = j;
      dis[total] = round(f[signs[i].s][city[j]] - signs[i].dis);
      total++;
    }
    // Sort cities.
    for (int p = 0; p < total; p++) {
      for (int q = p + 1; q < total; q++) {
        if (dis[q] < dis[p] ||
            (dis[q] == dis[p] && name[ids[q]] < name[ids[p]])) {
          swap(dis[p], dis[q]);
          swap(ids[p], ids[q]);
        }
      }
    }
    // Output.
    if (i > 0)
      cout << endl;
    for (int j = 0; j < total; j++)
      cout << setw(20) << left << name[ids[j]] << dis[j] << endl;
  }
  return 0;
}
