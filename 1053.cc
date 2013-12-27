#include <iostream>
#include <string>
using namespace std;

string card[12];

bool is_set(int a, int b, int c) {
  for (int i = 0; i < 4; i++) {
    if (card[a][i] == card[b][i] && card[b][i] == card[c][i]) continue;
    if (card[a][i] != card[b][i] && card[a][i] != card[c][i] &&
        card[b][i] != card[c][i]) continue;
    return false;
  }
  return true;
}

int main() {
  bool first = true;
  while (cin >> card[0]) {
    for (int i = 1; i < 12; i++)
      cin >> card[i];
    if (first)
      first = false;
    else
      cout << endl;
    cout << "CARDS: ";
    for (int i = 0; i < 12; i++)
      cout << ' ' << card[i];
    cout << endl;
    int id = 0;
    cout << "SETS:   ";
    for (int i = 0; i < 12; i++) {
      for (int j = i + 1; j < 12; j++) {
        for (int k = j + 1; k < 12; k++) {
          if (is_set(i, j, k)) {
            id++;
            if (id > 1) cout << "        ";
            cout << id << ".  " << card[i] << ' ' << card[j] << ' ' << card[k];
            cout << endl;
          }
        }
      }
    }
    if (id == 0)
      cout << "*** None Found ***" << endl;
  }
  return 0;
}
