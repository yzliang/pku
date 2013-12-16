#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    // Read input.
    string w[3][2];
    int result[3];
    for (int j = 0; j < 3; j++) {
      string x;
      cin >> w[j][0] >> w[j][1] >> x;
      if (x == "even")
        result[j] = 0;
      else if (x == "up")
        result[j] = 1;
      else
        result[j] = -1;
    }
    // Enumerate.
    int val[12];
    for (int j = 0; j < 12; j++) {  // j is the counterfeit.
      memset(val, 0, sizeof(val));
      bool found = false;
      for (int k = -1; k <= 1; k += 2) {
        val[j] = k;
        // Verify rules.
        bool valid = true;
        for (int p = 0; p < 3; p++) {
          int left = 0, right = 0;
          for (int q = 0; q < w[p][0].size(); q++)
            left += val[w[p][0][q] - 'A'];
          for (int q = 0; q < w[p][1].size(); q++)
            right += val[w[p][1][q] - 'A'];
          if (!(left == right && result[p] == 0 ||
                (left - right) * result[p] > 0)) {
            valid = false;
            break;
          }
        }
        if (valid) {
          found = true;
          cout << (char) ('A' + j) << " is the counterfeit coin and it is ";
          cout << (k == -1 ? "light." : "heavy.") << endl;
        }
      }
      if (found) break;
    }
  }
  return 0;
}
