#include <iostream>
#include <string>
using namespace std;

int main() {
  string x;
  while (cin >> x) {
    if (x == "-1") break;
    // Iterations.
    string num[30];
    num[0] = x;
    for (int i = 0; i < 15; i++) {
      int count[10] = {0};
      for (int j = 0; j < num[i].size(); j++)
        count[num[i][j] - '0']++;
      for (int j = 0; j < 10; j++) {
        if (count[j] > 0) {
          int len = 0;
          char buffer[4];
          while (count[j] > 0) {
            buffer[len++] = '0' + count[j] % 10;
            count[j] /= 10;
          }
          for (; len > 0; len--)
            num[i + 1] += buffer[len - 1];
          num[i + 1] += (char) ('0' + j);
        }
      }
    }
    if (num[0] == num[1]) {
      cout << x << " is self-inventorying" << endl;
      continue;
    }
    bool output = false;
    for (int i = 1; i < 15; i++) {
      if (num[i] == num[i + 1]) {
        cout << x << " is self-inventorying after " << i << " steps" << endl;
        output = true;
        break;
      }
    }
    if (output) continue;
    output = false;
    for (int i = 0; i < 15; i++) {
      for (int j = i + 2; j <= 15; j++) {
        if (num[i] == num[j]) {
          output = true;
          cout << x << " enters an inventory loop of length " << j - i << endl;
          break;
        }
      }
      if (output) break;
    }
    if (!output)
      cout << x << " can not be classified after 15 iterations" << endl;
  }
  return 0;
}
