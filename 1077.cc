#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int q[400000], f[400000];
char op[400000];
int head = 0, tail = 1, ans = -1;
const int SIZE = 999983;
int hash[SIZE];

bool hash_put(int x) {
  int k = x % SIZE;
  while (hash[k] != 0 && hash[k] != x)
    k++;
  if (hash[k] == 0) {
    hash[k] = x;
    return true;
  } else
    return false;
}

int get_zero(int x) {
  for (int i = 8; i >= 0; i--) {
    if (x % 10 == 0)
      return i;
    else
      x /= 10;
  }
}

void dump(int i) {
  string ops;
  for (; i > 0; i = f[i])
    ops.append(1, op[i]);
  reverse(ops.begin(), ops.end());
  cout << ops << endl;
}

void insert(int x, char o) {
  if (x == 123456780) ans = tail;
  q[tail] = x;
  f[tail] = head;
  op[tail++] = o;
}

int swap(int x, int i, int j) {
  static const int mask[9] = {100000000, 10000000, 1000000, 100000, 10000, 1000,
    100, 10, 1};
  int fig = (x / mask[j]) % 10;
  x = x - fig * mask[j] + fig * mask[i];
  return x;
}

int main() {
  for (int i = 0; i < 9; i++) {
    char c;
    cin >> c;
    q[0] = q[0] * 10 + (c == 'x' ? 0 : c - '0');
  }
  if (q[0] == 123456780) {
    cout << endl;
    return 0;
  }
  f[0] = -1;
  hash_put(q[0]);
  while (head < tail && ans == -1) {
    int pos = get_zero(q[head]);
    if (pos % 3 < 2) {
      int next = swap(q[head], pos, pos + 1);
      if (hash_put(next)) insert(next, 'r');
    }
    if (pos % 3 > 0) {
      int next = swap(q[head], pos, pos - 1);
      if (hash_put(next)) insert(next, 'l');
    }
    if (pos < 6) {
      int next = swap(q[head], pos, pos + 3);
      if (hash_put(next)) insert(next, 'd');
    }
    if (pos > 3) {
      int next = swap(q[head], pos, pos - 3);
      if (hash_put(next)) insert(next, 'u');
    }
    head++;
  }
  if (ans == -1)
    cout << "unsolvable" << endl;
  else
    dump(ans);
  return 0;
}
