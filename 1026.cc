#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int n;
  int a[200];
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      a[i]--;
    }
    string line;
    getline(cin, line);
    while (getline(cin, line)) {
      if (line == "0") break;
      int k = atoi(line.c_str());
      if (k == 0) break;
      string s1, s2;
      s1 = line.substr(line.find(' ') + 1);
      if (s1[s1.size() - 1] == '\r')
        s1.resize(s1.size() - 1);
      s1.append(n - s1.size(), ' ');
      s2.resize(s1.size());
      for (int i = 0; i < n; i++) {
        if (s2[i] != '\0') continue;
        vector<int> cycle(1, i);
        for (int j = a[i]; j != i; j = a[j])
          cycle.push_back(j);
        for (int j = 0; j < cycle.size(); j++) {
          s2[cycle[(j + k) % cycle.size()]] = s1[cycle[j]];
        }
      }
      cout << s2 << endl;
    }
    cout << endl;
  }
  return 0;
}
