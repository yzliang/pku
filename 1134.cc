#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

// t1: #times when a number is used (<= 9);
// t2: #times when two numbers (of two directions) co-occur (<= 3);
// t3: #times when three numbers (of all directions) co-occur (<= 1);
int t1[9], t2[3][6], t3[3][6][9];
int a[5], b[5], c[5];
int inv_list[5][5][2] = {
  {{2, 0}, {3, 1}, {4, 2}},
  {{1, 0}, {2, 1}, {3, 2}, {4, 3}},
  {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}},
  {{0, 1}, {1, 2}, {2, 3}, {3, 4}},
  {{0, 2}, {1, 3}, {2, 4}}
};
int total;  // #pattern
int freq[6][3][3];

void dump() {
  cout << "dir1: ";
  for (int i = 0; i < 5; i++) {
    cout << ' ' << a[i];
  }
  cout << endl;
  cout << "dir2: ";
  for (int i = 0; i < 5; i++) {
    cout << ' ' << b[i] - 3;
  }
  cout << endl;
  cout << "dir3: ";
  for (int i = 0; i < 5; i++) {
    cout << ' ' << c[i] - 6;
  }
  cout << endl;
  cout << "====================" << endl;
}

void save_pattern() {
  // The pattern itself has nothing to do with the final score.
  // Just need to record the frequency of each number.
  for (int i = 0; i < 5; i++) {
    int len = 5 - abs(i - 2);
    freq[total][0][a[i]] += len;
    freq[total][1][b[i] - 3] += len;
    freq[total][2][c[i] - 6] += len;
  }
  for (int i = 0; i < 3; i++)
    sort(freq[total][i], freq[total][i] + 3, greater<int>());
  total++;
}

void find2(int p) {
  if (p == 5) {
    if (c[0] == 6 && c[1] <= 7 && c[2] <= c[1] + 1)
      save_pattern();
    return;
  }
  for (int i = 6; i < 9; i++) {
    int len = 5 - abs(p - 2);
    if (t1[i] + len > 9)
      continue;
    // Update.
    for (int j = 0; j < len; j++) {
      const int& p0 = inv_list[p][j][0];
      const int& p1 = inv_list[p][j][1];
      t3[a[p0]][b[p1]][i]++;
    }
    // Examine.
    bool ok = true;
    for (int j = 0; j < len; j++) {
      const int& p0 = inv_list[p][j][0];
      const int& p1 = inv_list[p][j][1];
      if (t3[a[p0]][b[p1]][i] > 1) {
        ok = false;
        break;
      }
    }
    // Search & backtrack.
    if (ok) {
      t1[i] += len;
      c[p] = i;
      find2(p + 1);
      t1[i] -= len;
    }
    for (int j = 0; j < len; j++) {
      const int& p0 = inv_list[p][j][0];
      const int& p1 = inv_list[p][j][1];
      t3[a[p0]][b[p1]][i]--;
    }
  }
}

void find1(int p) {
  if (p == 5) {
    if (b[0] == 3 && b[1] <= 4 && b[2] <= b[1] + 1)
      find2(0);
    return;
  }
  for (int i = 3; i < 6; i++) {
    int len = 5 - abs(p - 2);
    if (t1[i] + len > 9)
      continue;
    // Update.
    int l = max(p - 2, 0), r = min(p + 3, 5);
    for (int j = l; j < r; j++)
      t2[a[j]][i] += 1;
    // Examine.
    bool ok = true;
    for (int j = l; j < r; j++) {
      if (t2[a[j]][i] > 3) {
        ok = false;
        break;
      }
    }
    // Search & backtrack.
    if (ok) {
      t1[i] += len;
      b[p] = i;
      find1(p + 1);
      t1[i] -= len;
    }
    for (int j = l; j < r; j++)
      t2[a[j]][i] -= 1;
  }
}

void find0(int p) {
  if (p == 5) {
    if (a[0] == 0 && a[1] <= 1 && a[2] <= a[1] + 1)
      find1(0);
    return;
  }
  for (int i = 0; i < 3; i++) {
    int len = 5 - abs(p - 2);
    if (t1[i] + len > 9)
      continue;
    a[p] = i;
    t1[i] += len;
    find0(p + 1);
    t1[i] -= len;
  }
}

int main() {
  // Search for patterns.
  total = 0;
  find0(0);
  // Solve.
  int n;
  int num[3][3];
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++)
        cin >> num[j][k];
      sort(num[j], num[j] + 3, greater<int>());
    }
    // Try all patterns.
    int best = 0;
    for (int i = 0; i < total; i++) {
      int score = 0;
      for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++)
          score += num[j][k] * freq[i][j][k];
      best = max(best, score);
    }
    cout << "Test #" << i << endl << best << endl << endl;
  }
  return 0;
}
