#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Pixel {
  int x, y;
  Pixel(int x, int y) : x(x), y(y) {}
};

int n, r, c;
vector<Pixel> fonts[80];
char map[80][10][80];
int num[10][80];

int main() {
  int id = 1;
  while (cin >> n >> r >> c) {
    if (n == 0 && r == 0 && c == 0)
      break;
    memset(num, 0, sizeof(num));
    for (int i = 0; i < n; i++)
      fonts[i].clear();
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < c; k++) {
          cin >> map[j][i][k];
          if (map[j][i][k] == 'o') {
            num[i][k]++;
            fonts[j].push_back(Pixel(i, k));
          }
        }
      }
    }
    bool failed = false;
    for (int i = 0; i < n; i++) {
      bool found = false;
      // try one.
      for (int j = 0; j < fonts[i].size(); j++) {
        if (num[fonts[i][j].x][fonts[i][j].y] == 1) {
          found = true;
          map[i][fonts[i][j].x][fonts[i][j].y] = '#';
          break;
        }
      }
      if (found) continue;
      // try two.
      for (int j = 0; j < fonts[i].size(); j++) {
        int x1 = fonts[i][j].x, y1 = fonts[i][j].y;
        for (int k = j + 1; k < fonts[i].size(); k++) {
          int x2 = fonts[i][k].x, y2 = fonts[i][k].y;
          bool unique = true;
          for (int l = 0; l < n; l++) {
            if (l != i && map[l][x1][y1] != '.' && map[l][x2][y2] != '.') {
              unique = false;
              break;
            }
          }
          if (unique) {
            found = true;
            map[i][x1][y1] = map[i][x2][y2] = '#';
            break;
          }
        }
        if (found) break;
      }
      if (!found) {
        failed = true;
        break;
      }
    }
    cout << "Test " << id++ << endl;
    if (failed)
      cout << "impossible" << endl;
    else {
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < n; j++) {
          if (j > 0) cout << ' ';
          for (int k = 0; k < c; k++)
            cout << map[j][i][k];
        }
        cout << endl;
      }
    }
  }
  return 0;
}
