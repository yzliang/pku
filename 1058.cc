#include <cstring>
#include <iostream>
#include <string>
using namespace std;

string old[3][4];
bool used[16][16];
bool set[2][16];
int table[2][4][4];

bool read_input() {
  string s;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (!(cin >> s)) return false;
      old[i][j] = s;
      for (int k = 0; k < 4; k++)
        for (int l = 0; l < 4; l++)
          used[s[k] - 'A'][s[l] - 'A'] = true;
    }
  }
  return true;
}

// day, table, person
bool schedule(int d, int t, int p) {
  if (d == 2) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        if (j > 0) cout << ' ';
        cout << old[i][j];
      }
      cout << endl;
    }
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 4; j++) {
        if (j > 0) cout << ' ';
        for (int k = 0; k < 4; k++)
          cout << (char)('A' + table[i][j][k]);
      }
      cout << endl;
    }
    return true;
  } else if (t == 4) {
    return schedule(d + 1, 0, 0);
  } else if (p == 4) {
    return schedule(d, t + 1, 0);
  } else if (p == 0) {
    for (int i = 0; i < 16; i++) {
      if (set[d][i]) continue;
      set[d][i] = true;
      table[d][t][0] = i;
      if (schedule(d, t, p + 1))
        return true;
      set[d][i] = false;
      break;
    }
    return false;
  } else {
    for (int i = table[d][t][p - 1] + 1; i < 16; i++) {
      if (set[d][i]) continue;
      bool meet = false;
      for (int j = 0; j < p; j++) {
        if (used[table[d][t][j]][i]) {
          meet = true;
          break;
        }
      }
      if (meet) continue;
      set[d][i] = true;
      for (int j = 0; j < p; j++)
        used[table[d][t][j]][i] = true;
      table[d][t][p] = i;
      if (schedule(d, t, p + 1))
        return true;
      set[d][i] = false;
      for (int j = 0; j < p; j++)
        used[table[d][t][j]][i] = false;
    }
    return false;
  }
}

int main() {
  bool first = true;
  while (true) {
    memset(used, 0, sizeof(used));
    memset(set, 0, sizeof(set));
    if (!read_input()) break;
    if (first)
      first = false;
    else
      cout << endl;
    if (!schedule(0, 0, 0))
      cout << "It is not possible to complete this schedule." << endl;
  }
  return 0;
}
