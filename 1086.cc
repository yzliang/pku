#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

const int pow4[] = {1, 4, 16, 64, 256};
int n, h; // 2^h = n
int map[512]; // fake id -> real id.
int image[16][16];
int leaf_id[256];

void mark_leaf(int id, int x, int y, int len) {
  if (len == 1)
    leaf_id[n * x + y] = id;
  else {
    mark_leaf(id * 4 + 1, x, y, len / 2);
    mark_leaf(id * 4 + 2, x, y + len / 2, len / 2);
    mark_leaf(id * 4 + 3, x + len / 2, y, len / 2);
    mark_leaf(id * 4 + 4, x + len / 2, y + len / 2, len / 2);
  }
}

void decode_password() {
  int id[256];
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    id[i] = leaf_id[y];
  }
  for (int level = h - 1; level >= 0; level--) {
    int total = pow4[level];
    int fake_id = (pow4[level + 1] - 1) / 3;
    for (int i = 0; i < total; i++) {
      for (int j = 0; j < 4; j++)
        map[fake_id++] = id[4 * i + j];
      id[i] = (id[4 * i] - 1) / 4;
    }
  }
}

void paint(int num, int value) {
  int ids[5];
  ids[0] = map[num];
  int i = 0;
  while (ids[i] > 0) {
    ids[i + 1] = (ids[i] - 1) / 4;
    i++;
  }
  int len = n, x = 0, y = 0;
  for (int j = i; j > 0; j--) {
    len /= 2;
    int delta = ids[j - 1] - ids[j] * 4;
    if (delta == 2 || delta == 4)
      y += len;
    if (delta == 3 || delta == 4)
      x += len;
  }
  for (int dx = 0; dx < len; dx++)
    for (int dy = 0; dy < len; dy++)
      image[x + dx][y + dy] = value;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cin >> n;
    h = log2(n);
    mark_leaf(0, 0, 0, n);
    decode_password();
    int m;
    cin >> m;
    for (int j = 0; j < m; j++) {
      int num, value;
      cin >> num >> value;
      paint(num, value);
    }
    if (i > 1) cout << endl;
    cout << "Case " << i << endl << endl;
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++)
        cout << setw(4) << image[j][k];
      cout << endl;
    }
  }
  return 0;
}
