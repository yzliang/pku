#include <cstdio>
#include <iostream>
using namespace std;

int f[20];

void precompute() {
  f[0] = 1;
  for (int i = 1; i < 20; i++)
    for (int j = 0; j <= i - 1; j++)
      f[i] += f[j] * f[i - 1 - j];
}

void make_tree(int num_nodes, int ord) {
  if (num_nodes == 0)
    return;
  else if (num_nodes == 1)
    cout << 'X';
  else {
    int num_left = 0, num_right = num_nodes - 1;
    while (ord >= f[num_left] * f[num_right])
      ord -= f[num_left++] * f[num_right--];
    if (num_left > 0) {
      cout << '(';
      make_tree(num_left, ord / f[num_right]);
      cout << ')';
    }
    cout << 'X';
    if (num_right > 0) {
      cout << '(';
      make_tree(num_right, ord % f[num_right]);
      cout << ')';
    }
  }
}

int main() {
  precompute();
  int n;
  while (cin >> n) {
    if (n == 0) break;
    int m = 1;  // number of nodes.
    while (n > f[m])
      n -= f[m++];
    make_tree(m, n - 1);
    cout << endl;
  }
  return 0;
}
