#include <iostream>
#include <vector>
using namespace std;

int n, k;
int val[1000];
int comp[100];
vector<int> l[100], r[100];

int sign(int x) {
  if (x < 0) return -1;
  if (x == 0) return 0;
  return 1;
}

bool check() {
  for (int i = 0; i < k; i++) {
    int l_sum = 0, r_sum = 0;
    for (int j = 0; j < l[i].size(); j++) {
      l_sum += val[l[i][j]];
      r_sum += val[r[i][j]];
    }
    if (sign(l_sum - r_sum) != comp[i]) return false;
  }
  return true;
}

int main() {
  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    int p, x;
    char c;
    cin >> p;
    for (int j = 0; j < p; j++) {
      cin >> x;
      l[i].push_back(x - 1);
    }
    for (int j = 0; j < p; j++) {
      cin >> x;
      r[i].push_back(x - 1);
    }
    cin >> c;
    if (c == '=')
      comp[i] = 0;
    else if (c == '<')
      comp[i] = -1;
    else
      comp[i] = 1;
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    bool found = false;
    val[i] = 1;
    if (check()) {
      found = true;
    } else {
      val[i] = -1;
      if (check()) found = true;
    }
    val[i] = 0;
    if (found) {
      if (ans > 0) {
        ans = 0;
        break;
      }
      ans = i + 1;
    }
  }
  cout << ans << endl;
  return 0;
}
