#include <cstring>
#include <iostream>
using namespace std;

const int map[10][7] = {
  {1, 1, 1, 0, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0},
  {1, 0, 1, 1, 1, 0, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {0, 1, 1, 1, 0, 1, 0},
  {1, 1, 0, 1, 0, 1, 1},
  {1, 1, 0, 1, 1, 1, 1},
  {1, 0, 1, 0, 0, 1, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1}
};

int s, n, len;
int num[8];
char a[23][105];

int main() {
  while (cin >> s >> n) {
    if (s == 0 && n == 0)
      break;
    if (n == 0) {
      len = 1;
      num[0] = 0;
    } else {
      len = 0;
      while (n > 0) {
        num[len++] = n % 10;
        n /= 10;
      }
    }
    int base = 0;
    memset(a, 0, sizeof(a));
    for (int i = len - 1; i >= 0; i--) {
      if (map[num[i]][0]) {
        for (int j = 0; j < s; j++)
          a[0][base + 1 + j] = '-';
      }
      if (map[num[i]][1]) {
        for (int j = 0; j < s; j++)
          a[1 + j][base] = '|';
      }
      if (map[num[i]][2]) {
        for (int j = 0; j < s; j++)
          a[1 + j][base + s + 1] = '|';
      }
      if (map[num[i]][3]) {
        for (int j = 0; j < s; j++)
          a[s + 1][base + 1 + j] = '-';
      }
      if (map[num[i]][4]) {
        for (int j = 0; j < s; j++)
          a[s + 2 + j][base] = '|';
      }
      if (map[num[i]][5]) {
        for (int j = 0; j < s; j++)
          a[s + 2 + j][base + s + 1] = '|';
      }
      if (map[num[i]][6]) {
        for (int j = 0; j < s; j++)
          a[s + s + 2][base + 1 + j] = '-';
      }
      base += s + 3;
    }
    for (int i = 0; i < 2 * s + 3; i++) {
      for (int j = 0; j < (s + 2) * len + len - 1; j++)
        cout << (a[i][j] > 0 ? a[i][j] : ' ');
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
