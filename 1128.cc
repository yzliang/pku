#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int h, w, total;
int min_x[26], max_x[26], min_y[26], max_y[26];
char map[30][31];
bool has[26], used[26];
bool cover[26][26];
int deg[26];
char order[26];
vector<string> ans;

void search(int p) {
  if (p == total) {
    ans.push_back(string(order, total));
    reverse(ans.back().begin(), ans.back().end());
    return;
  }
  for (int i = 0; i < 26; i++) {
    if (!has[i] || used[i] || deg[i] != 0) continue;
    order[p] = 'A' + i;
    used[i] = true;
    for (int j = 0; j < 26; j++) {
      if (cover[i][j])
        deg[j]--;
    }
    search(p + 1);
    // Backtracking.
    used[i] = false;
    for (int j = 0; j < 26; j++) {
      if (cover[i][j])
        deg[j]++;
    }
  }
}

int main() {
  while (cin >> h >> w) {
    for (int i = 0; i < 26; i++) {
      min_x[i] = min_y[i] = INT_MAX;
      max_x[i] = max_y[i] = INT_MIN;
    }
    memset(has, 0, sizeof(has));
    for (int i = 0; i < h; i++) {
      cin >> map[i];
      for (int j = 0; j < w; j++) {
        if (map[i][j] != '.') {
          int k = map[i][j] - 'A';
          has[k] = true;
          min_x[k] = min(min_x[k], j);
          max_x[k] = max(max_x[k], j);
          min_y[k] = min(min_y[k], i);
          max_y[k] = max(max_y[k], i);
        }
      }
    }
    total = 0;
    for (int i = 0; i < 26; i++)
      total += has[i];
    // Create DAG.
    memset(cover, 0, sizeof(cover));
    for (int i = 0; i < 26; i++) {
      if (!has[i]) continue;
      char c = 'A' + i;
      for (int j = min_x[i]; j <= max_x[i]; j++) {
        if (map[min_y[i]][j] != c)
          cover[map[min_y[i]][j] - 'A'][i] = true;
        if (map[max_y[i]][j] != c)
          cover[map[max_y[i]][j] - 'A'][i] = true;
      }
      for (int j = min_y[i] + 1; j < max_y[i]; j++) {
        if (map[j][min_x[i]] != c)
          cover[map[j][min_x[i]] - 'A'][i] = true;
        if (map[j][max_x[i]] != c)
          cover[map[j][max_x[i]] - 'A'][i] = true;
      }
    }
    memset(deg, 0, sizeof(deg));
    for (int i = 0; i < 26; i++) {
      if (!has[i]) continue;
      for (int j = 0; j < 26; j++) {
        if (cover[j][i])
          deg[i]++;
      }
    }
    // Search by topology.
    memset(used, 0, sizeof(used));
    ans.clear();
    search(0);
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++)
      cout << ans[i] << endl;
  }
  return 0;
}
