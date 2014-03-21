#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
  int k[3];
  while (cin >> k[0] >> k[1] >> k[2]) {
    if (k[0] == 0) break;
    string line;
    cin >> line;
    string s[3];
    int g[80];
    for (int i = 0; i < line.size(); i++) {
      if (line[i] >= 'a' && line[i] <= 'i')
        g[i] = 0;
      else if (line[i] >= 'j' && line[i] <= 'r')
        g[i] = 1;
      else
        g[i] = 2;
      s[g[i]] += line[i];
    }
    // Rotate.
    for (int i = 0; i < 3; i++) {
      if (!s[i].empty())
        k[i] %= s[i].size();
      reverse(s[i].begin(), s[i].end());
      reverse(s[i].begin(), s[i].begin() + k[i]);
      reverse(s[i].begin() + k[i], s[i].end());
    }
    // Decrypt.
    int next[3] = {0};
    string ans;
    for (int i = 0; i < line.size(); i++)
      ans += s[g[i]][next[g[i]]++];
    cout << ans << endl;
  }
  return 0;
}
