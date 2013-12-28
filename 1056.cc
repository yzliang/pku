#include <cstring>
#include <iostream>
#include <string>
using namespace std;

bool used[5000];

int main() {
  int t = 0;
  while (true) {
    memset(used, 0, sizeof(used));
    string s;
    bool ok = true, has_input = false;
    while (cin >> s) {
      if (s[0] == '9') break;
      has_input = true;
      int node = 0;
      for (int i = 0; i < s.size(); i++) {
        node = node * 2 + 1 + (s[i] - '0');
        if (used[node]) ok = false;
      }
      used[node] = true;
    }
    if (!has_input) break;
    cout << "Set " << ++t << " is ";
    if (!ok) cout << "not ";
    cout << "immediately decodable" << endl;
  }
  return 0;
}
