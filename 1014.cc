#include <cstring>
#include <iostream>
using namespace std;

int sum, half, max_m;
int m[6], amount[6];
bool f[120001];
int total;
int g[120001];

bool compute() {
  memset(f, 0, sizeof(f));
  total = 0;
  // Must use the max marble.
  for (int i = 1; i <= m[max_m]; i++) {
    if (max_m * i > half) break;
    if (max_m * i == half) return true;
    f[max_m * i] = true;
    g[total++] = max_m * i;
  }
  // Try 5,4,3,2,1.
  for (int i = max_m - 1; i >= 1; i--) {
    int tail = total;
    for (int j = 0; j < total; j++) {
      int min_k = 0;
      if (half > g[j] + amount[i - 1])
        min_k = (half - g[j] - amount[i - 1] + i - 1) / i;
      for (int k = min_k; k <= m[i]; k++) {
        int value = g[j] + k * i;
        if (value > half) break;
        if (f[value]) continue;
        f[value] = true;
        g[tail++] = value;
        if (value == half) return true;
      }
    }
    total = tail;
  }
  return false;
}

int main() {
  int t = 0;
  while (true) {
    sum = 0;
    amount[0] = 0;
    max_m = 0;
    for (int i = 1; i <= 6; i++) {
      cin >> m[i];
      if (m[i] > 0) max_m = i;
      sum += i * m[i];
      amount[i] = amount[i - 1] + i * m[i];
    }
    if (sum == 0) break;
    cout << "Collection #" << ++t << ':' << endl;
    bool can = false;
    if (sum % 2 == 0) {
      half = sum / 2;
      can = compute();
    }
    cout << (can ? "Can" : "Can't") << " be divided." << endl;
    cout << endl;
  }
  return 0;
}
