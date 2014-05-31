#include <iostream>
#include <string>
using namespace std;

const int rd[] = {1, 2, 3, 0};
char map[32][33];

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    int x, y;
    cin >> x >> y;
    string s;
    cin >> s;
    for (int j = 0; j < 32; j++)
      for (int k = 0; k < 32; k++)
        map[j][k] = '.';
    // Simulate.
    for (int j = 0; j < s.size() - 1; j++) {
      switch (s[j]) {
        case 'E':
          map[y - 1][x] = 'X';
          x++;
          break;
        case 'S':
          map[y - 1][x - 1] = 'X';
          y--;
          break;
        case 'W':
          map[y][x - 1] = 'X';
          x--;
          break;
        case 'N':
          map[y][x] = 'X';
          y++;
          break;
      }
    }
    // Output.
    cout << "Bitmap #" << i << endl;
    for (int j = 31; j >= 0; j--)
      cout << map[j] << endl;
    cout << endl;
  }
  return 0;
}
