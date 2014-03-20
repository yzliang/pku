#include <iostream>
#include <string>
using namespace std;

const int p2[] = {1, 2, 4, 8, 16, 32, 64, 128};
int n, m;
int order[7];
string values;

int main() {
  int id = 1;
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < n; i++) {
      string var;
      cin >> var;
      order[i] = var[1] - '0' - 1;
    }
    cin >> values;
    cin >> m;
    cout << "S-Tree #" << id++ << ':' << endl;
    for (int i = 0; i < m; i++) {
      string input;
      cin >> input;
      int l = 0, r = p2[n];
      for (int j = 0; j < n; j++) {
        if (input[order[j]] == '0')
          r = l + (r - l) / 2;
        else
          l = l + (r - l) / 2;
      }
      cout << values[l];
    }
    cout << endl << endl;
  }
  return 0;
}
