#include <algorithm>
#include <iostream>
using namespace std;

int n;
bool g[30][30];

int main() {
  int id;
  while (cin >> id) {
    n = max(id, n);
    int m, other;
    cin >> m;
    for (int i = 0; i < m; i++) {
      cin >> other;
      g[id - 1][other - 1] = true;
    }
  }
  int a[30];
  for (int i = 0; i < n; i++) a[i] = i;
  int ans = n;
  for (int t = 0; t < 10000; t++) {
    random_shuffle(a, a + n);
    int max_deg = 0;
    for (int i = 0; i < n / 2; i++) {
      int deg = 0;
      for (int j = 0; j < n / 2; j++)
        if (j != i && !g[a[i]][a[j]]) deg++;
      max_deg = max(max_deg, deg);
    }
    for (int i = n / 2; i < n; i++) {
      int deg = 0;
      for (int j = n / 2; j < n; j++)
        if (j != i && !g[a[i]][a[j]]) deg++;
      max_deg = max(max_deg, deg);
    }
    ans = min(ans, max_deg);
  }
  cout << ans << endl;
  return 0;
}
