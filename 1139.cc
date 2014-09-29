#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int n, ic, im;
bool gc[100][100], gm[100][100];
bool cr[100], cm[100];
bool f[201][100];

void walk(bool g[100][100], bool r[100], int init_pos) {
  memset(r, 0, sizeof(bool[100]));
  r[init_pos] = true;
  queue<int> q;
  q.push(init_pos);
  while (!q.empty()) {
    int pos = q.front();
    q.pop();
    for (int i = 0; i < n; i++) {
      if (g[pos][i] && !r[i]) {
        r[i] = true;
        q.push(i);
      }
    }
  }
}

struct State {
  int len, pos;
  State(int len, int pos) : len(len), pos(pos) {}
};

void solve() {
  if (ic == im) {
    cout << "Y N" << endl;
    return;
  }
  bool ans1 = false, ans2 = false;
  // Find the cat's reachable rooms.
  walk(gc, cr, ic);
  // Find the mouse's reachable rooms.
  walk(gm, cm, im);
  // Solve 1.
  for (int i = 0; i < n; i++) {
    if (cr[i] && cm[i])
      ans1 = true;
  }
  // Solve 2.
  memset(f, 0, sizeof(f));
  queue<State> q;
  q.push(State(0, im));
  while (!q.empty() && !ans2) {
    int len = q.front().len;
    int pos = q.front().pos;
    q.pop();
    if (cr[pos]) continue;  // Cat's territory.
    if (len >= 2 && pos == im)
      ans2 = true;
    else if (len < 2 * n) {
      for (int i = 0; i < n; i++) {
        if (gm[pos][i] && !f[len + 1][i]) {
          f[len + 1][i] = true;
          q.push(State(len + 1, i));
        }
      }
    }
  }
  cout << (ans1 ? 'Y' : 'N') << ' ' << (ans2 ? 'Y' : 'N') << endl;
}

int main() {
  int num_cases;
  for (cin >> num_cases; num_cases > 0; num_cases--) {
    cin >> n >> ic >> im;
    ic--;
    im--;
    int x, y;
    memset(gc, 0, sizeof(gc));
    while (cin >> x >> y) {
      if (x == -1) break;
      gc[x - 1][y - 1] = true;
    }
    memset(gm, 0, sizeof(gm));
    while (cin >> x >> y) {
      if (x == -1) break;
      gm[x - 1][y - 1] = true;
    }
    solve();
  }
  return 0;
}
