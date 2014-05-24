#include <algorithm>
#include <iostream>
using namespace std;

int n, f, m;  // m is the number of firehouses.
int id[20];
int g[21][21];
bool visit[21];
int d[21], from[21];

const int BIG = 1000000000;

void dijkstra() {
  for (int i = 1; i <= n; i++)
    d[i] = BIG;
  d[f] = 0;
  while (true) {
    int j = -1;
    for (int i = 1; i <= n; i++) {
      if (!visit[i] && (j == -1 || d[j] > d[i]))
        j = i;
    }
    if (j == -1) break;
    visit[j] = true;
    for (int i = 1; i <= n; i++) {
      if (!visit[i] && g[j][i] != -1 && d[j] + g[j][i] < d[i]) {
        d[i] = d[j] + g[j][i];
        from[i] = j;
      }
    }
  }
}

bool compare_distance(const int& i, const int& j) {
  if (d[i] != d[j])
    return d[i] < d[j];
  else
    return i < j;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> g[j][i];
  cin >> f;
  while (cin >> id[m])
    m++;
  dijkstra();
  sort(id, id + m, compare_distance);
  cout << "Org\tDest\tTime\tPath" << endl;
  for (int i = 0; i < m; i++) {
    cout << id[i] << '\t' << f << '\t' << d[id[i]];
    for (int j = id[i]; j != f; j = from[j])
      cout << '\t' << j;
    cout << '\t' << f << endl;
  }
  return 0;
}
