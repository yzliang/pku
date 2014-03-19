#include <cstring>
#include <iostream>
using namespace std;

int m;
int o[11][11];
int a[30][30];  // 0: empty, -1: oxygen, 1~4: hydrogen

int main() {
  int id = 1;
  while (cin >> m) {
    if (m == 0)
      break;
    memset(a, 0, sizeof(a));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        cin >> o[i][j];
        a[i * 2][j * 2 + 1] = -1;
        if (o[i][j] == 1) {
          a[i * 2][j * 2] = 1;
          a[i * 2][j * 2 + 2] = 3;
        } else if (o[i][j] == -1) {
          a[i * 2 - 1][j * 2 + 1] = 2;
          a[i * 2 + 1][j * 2 + 1] = 4;
        }
      }
    }
    // Deal with normal oxygen atoms.
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        if (o[i][j] != 0)
          continue;
        // Horizontal atom.
        if (a[i * 2][j * 2] == 0)
          a[i * 2][j * 2] = 1;
        else
          a[i * 2][j * 2 + 2] = 3;
        // Vertical atom.
        if (i > 0 && a[i * 2 - 1][j * 2 + 1] == 0)
          a[i * 2 - 1][j * 2 + 1] = 2;
        else
          a[i * 2 + 1][j * 2 + 1] = 4;
      }
    }
    // Print.
    if (id > 1)
      cout << endl;
    cout << "Case " << id++ << ':' << endl << endl;
    for (int i = 0; i < 4 * m + 3; i++)
      cout << '*';
    cout << endl;
    for (int i = 0; i < 2 * m - 1; i++) {
      if (i > 0) {
        cout << '*';
        for (int j = 0; j < 2 * m + 1; j++) {
          if (j > 0)
            cout << ' ';
          if (a[i][j] == 4 || (a[i][j] == -1 && a[i - 1][j] == 2))
            cout << '|';
          else
            cout << ' ';
        }
        cout << '*' << endl;
      }
      cout << '*';
      for (int j = 0; j < 2 * m + 1; j++) {
        if (j > 0) {
          if (a[i][j - 1] == 1 || a[i][j] == 3)
            cout << '-';
          else
            cout << ' ';
        }
        if (a[i][j] == -1)
          cout << 'O';
        else if (a[i][j] > 0)
          cout << 'H';
        else
          cout << ' ';
      }
      cout << '*' << endl;
    }
    for (int i = 0; i < 4 * m + 3; i++)
      cout << '*';
    cout << endl;
  }
  return 0;
}
