#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int n, total;
int black, white;
bool know[101][101];
int group[101];
int color[101];  // 1: black, 2: white
int diff[101];
bool f[101][201], g[101][201];
vector<int> ans1, ans2;

bool paint(int id, int c) {
  group[id] = total + 1;
  color[id] = c;
  if (c == 1)
    black++;
  else
    white++;
  for (int i = 1; i <= n; i++) {
    if (i != id && !(know[id][i] && know[i][id])) {
      if (color[i] == 0) {
        if (!paint(i, c == 1 ? 2 : 1))
          return false;
      } else if (color[i] == c)
        return false;
    }
  }
  return true;
}

void assign(int target) {
  for (int i = total; i > 0; i--) {
    if (g[i][target]) {
      // Reverse.
      for (int j = 1; j <= n; j++) {
        if (group[j] != i) continue;
        if (color[j] == 1)
          ans2.push_back(j);
        else
          ans1.push_back(j);
      }
      target += diff[i];
    } else {
      for (int j = 1; j <= n; j++) {
        if (group[j] != i) continue;
        if (color[j] == 1)
          ans1.push_back(j);
        else
          ans2.push_back(j);
      }
      target -= diff[i];
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int x;
    while (cin >> x) {
      if (x == 0) break;
      know[i][x] = true;
    }
  }
  // Look and examine components.
  for (int i = 1; i <= n; i++) {
    if (group[i] != 0) continue;
    black = white = 0;
    if (!paint(i, 1)) {
      cout << "No solution" << endl;
      return 0;
    }
    diff[++total] = black - white;
  }
  // DP.
  f[0][0 + 100] = true;
  for (int i = 0; i < total; i++) {
    for (int j = -n + 100; j <= n + 100; j++) {
      if (!f[i][j]) continue;
      int target = j + diff[i + 1];
      f[i + 1][target] = true;
      g[i + 1][target] = false;
      target = j - diff[i + 1];
      f[i + 1][target] = true;
      g[i + 1][target] = true;
    }
  }
  // Find solution.
  for (int i = 0; i <= n; i++) {
    if (f[total][-i + 100]) {
      assign(-i + 100);
      break;
    }
    if (f[total][i + 100]) {
      assign(i + 100);
      break;
    }
  }
  // Output.
  cout << ans1.size();
  for (int i = 0; i < ans1.size(); i++)
    cout << ' ' << ans1[i];
  cout << endl;
  cout << ans2.size();
  for (int i = 0; i < ans2.size(); i++)
    cout << ' ' << ans2[i];
  cout << endl;
  return 0;
}
