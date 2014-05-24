#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n;
bool used[26];
bool out[50][26], block[50][26];
vector<int> graph[50];

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    if (s[0] != '.') {
      for (int j = 0; j < s.size(); j++) {
        out[i][s[j] - 'A'] = true;
        used[s[j] - 'A'] = true;
      }
    }
    cin >> s;
    if (s[0] != '.') {
      for (int j = 0; j < s.size(); j++) {
        block[i][s[j] - 'A'] = true;
        used[s[j] - 'A'] = true;
      }
    }
  }
  int x, y;
  while (cin >> x >> y) {
    if (x == 0 && y == 0)
      break;
    graph[x - 1].push_back(y - 1);
  }
  // Compute the circulation for each chemical.
  for (int i = 0; i < 26; i++) {
    if (!used[i]) continue;
    bool update = true;
    while (update) {
      update = false;
      for (int j = 0; j < n; j++) {
        if (!out[j][i]) continue;
        for (vector<int>::iterator k = graph[j].begin(); k != graph[j].end();
            k++) {
          if (!block[*k][i] && !out[*k][i]) {
            out[*k][i] = true;
            update = true;
          }
        }
      }
    }
  }
  // Output.
  for (int i = 0; i < n; i++) {
    cout << ':';
    for (int j = 0; j < 26; j++) {
      if (out[i][j])
        cout << (char) (j + 'A');
    }
    cout << ':' << endl;
  }
  return 0;
}
