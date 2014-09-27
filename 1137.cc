#include <cstring>
#include <iostream>
using namespace std;

int r, d, s;
bool go[10][10], ctr[10][10];
bool visit[1024 << 4];
int queue[20000], from[20000], steps[20000], op1[20000], op2[20000];
int head, tail;

void dump(int i) {
  if (from[i] > 0)
    dump(from[i]);
  switch (op1[i]) {
    case 0:
      cout << "- Move to room " << op2[i] + 1 << '.';
      break;
    case 1:
      cout << "- Switch off light in room " << op2[i] + 1 << '.';
      break;
    case 2:
      cout << "- Switch on light in room " << op2[i] + 1 << '.';
      break;
  }
  cout << endl;
}

void solve() {
  if (r == 1) {
    cout << "The problem can be solved in 0 steps:" << endl << endl;
    return;
  }
  int target = ((1 << (r - 1)) << 4) | (r - 1);
  head = tail = 0;
  queue[0] = 1 << 4;
  steps[0] = 0;
  memset(visit, 0, sizeof(visit));
  visit[1 << 4] = true;
  while (head <= tail) {
    int pos = queue[head] & 0xf;
    int lights = queue[head] >> 4;
    // Move.
    for (int i = 0; i < r; i++) {
      if (i != pos && (lights & (1 << i)) && go[pos][i]) {
        int ns = (lights << 4) | i;
        if (!visit[ns]) {
          visit[ns] = true;
          queue[++tail] = ns;
          from[tail] = head;
          steps[tail] = steps[head] + 1;
          op1[tail] = 0;
          op2[tail] = i;
        }
      }
    }
    // Off.
    for (int i = 0; i < r; i++) {
      if (i != pos && ctr[pos][i] && (lights & (1 << i))) {
        int ns = ((lights & ~(1 << i)) << 4) | pos;
        if (!visit[ns]) {
          visit[ns] = true;
          queue[++tail] = ns;
          from[tail] = head;
          steps[tail] = steps[head] + 1;
          op1[tail] = 1;
          op2[tail] = i;
          if (ns == target) {
            cout << "The problem can be solved in " << steps[tail] << " steps:";
            cout << endl;
            dump(tail);
            cout << endl;
            return;
          }
        }
      }
    }
    // On.
    for (int i = 0; i < r; i++) {
      if (ctr[pos][i] && (lights & (1 << i)) == 0) {
        int ns = ((lights | (1 << i)) << 4) | pos;
        if (!visit[ns]) {
          visit[ns] = true;
          queue[++tail] = ns;
          from[tail] = head;
          steps[tail] = steps[head] + 1;
          op1[tail] = 2;
          op2[tail] = i;
        }
      }
    }
    head++;
  }
  cout << "The problem cannot be solved." << endl << endl;
}

int main() {
  int id = 1;
  while (cin >> r >> d >> s) {
    if (r == 0 && d == 0 && s == 0)
      break;
    memset(go, 0, sizeof(go));
    for (int i = 0; i < d; i++) {
      int x, y;
      cin >> x >> y;
      go[x - 1][y - 1] = go[y - 1][x - 1] = true;
    }
    memset(ctr, 0, sizeof(ctr));
    for (int i = 0; i < s; i++) {
      int x, y;
      cin >> x >> y;
      ctr[x - 1][y - 1] = true;
    }
    cout << "Villa #" << id++ << endl;
    solve();
  }
  return 0;
}
