#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

// edges are encoded as 17-bit vector.
const unsigned tri[9] = {0x7, 0x98, 0x34, 0x160, 0x8600, 0xc80, 0x11800, 0x3100,
  0x26000};

int pos[11][11];

// 0 - A to move; 1 - B to move; f[i][j] - the max number of triangles to win.
int f[262144][2]; 

void init() {
  for (int i = 0; i < 262144; i++)
    f[i][0] = f[i][1] = -1;
  f[262143][0] = f[262143][1] = 0;
  pos[1][2] = 0;
  pos[1][3] = 1;
  pos[2][3] = 2;
  pos[2][4] = 3;
  pos[2][5] = 4;
  pos[3][5] = 5;
  pos[3][6] = 6;
  pos[4][5] = 7;
  pos[5][6] = 8;
  pos[4][7] = 9;
  pos[4][8] = 10;
  pos[5][8] = 11;
  pos[5][9] = 12;
  pos[6][9] = 13;
  pos[6][10] = 14;
  pos[7][8] = 15;
  pos[8][9] = 16;
  pos[9][10] = 17;
}

// Return the number of triangles won in this move.
int move(unsigned& s, int p) {
  unsigned ns = s;
  ns |= (1 << p);
  int won = 0;
  for (int i = 0; i < 9; i++) {
    if ((s & tri[i]) != tri[i] && (ns & tri[i]) == tri[i])
      won++;
  }
  s = ns;
  return won;
}

void compute(unsigned s, int t) {
  if (f[s][t] != -1) return;
  for (int i = 0; i < 18; i++) {
    if ((s & (1 << i)) != 0) continue;
    unsigned ns = s;
    int won = move(ns, i);
    if (won > 0) {
      compute(ns, t);
      f[s][t] = max(f[s][t], f[ns][t] + won);
    } else {
      int rest = 0;
      for (int j = 0; j < 9; j++) {
        if ((ns & tri[j]) != tri[j])
          rest++;
      }
      compute(ns, 1 - t);
      f[s][t] = max(f[s][t], rest - f[ns][1 - t]);
    }
  }
}

int main() {
  init();
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    // Simulate the game to the known moves.
    int m;
    unsigned state = 0;
    int scores[2] = {0};  // scores.
    int turn = 0;  // 0 - A to move, 1 - B to move.
    cin >> m;
    for (int j = 0; j < m; j++) {
      int x, y;
      cin >> x >> y;
      int num_tri = move(state, pos[x][y]);
      scores[turn] += num_tri;
      if (num_tri == 0)
        turn = 1 - turn;
    }
    if (turn == 0) {
      compute(state, 0);
      scores[0] += f[state][0];
      scores[1] = 9 - scores[0];
    } else {
      compute(state, 1);
      scores[1] += f[state][1];
      scores[0] = 9 - scores[1];
    }
    cout << "Game " << i << ": ";
    cout << (scores[0] > scores[1] ? 'A' : 'B');
    cout << " wins." << endl;
  }
  return 0;
}
