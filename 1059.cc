#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

vector<int> die;
int n;
int jump[100];
bool miss[100], extra[100];

int find_winner() {
  bool stop[6] = {0};
  int pos[6] = {0};
  int p = 0;
  for (int i = 0; i < die.size(); i++) {
    // Find the next available player.
    while (stop[p]) {
      stop[p] = false;
      p = (p + 1) % n;
    }
    if (pos[p] + die[i] <= 100)
      pos[p] += die[i];
    if (pos[p] == 100) return p;
    if (jump[pos[p]] != -1)
      pos[p] = jump[pos[p]];
    if (extra[pos[p]])
      continue;
    else if (miss[pos[p]]) {
      stop[p] = true;
      p = (p + 1) % n;
    } else
      p = (p + 1) % n;
  }
  return 0;
}

int main() {
  int x, y;
  while (cin >> x) {
    if (x == 0) break;
    die.push_back(x);
  }
  while (cin >> n) {
    if (n == 0) break;
    fill_n(jump, 100, -1);
    while (cin >> x >> y) {
      if (x == 0 && y == 0) break;
      jump[x] = y;
    }
    memset(miss, 0, sizeof(miss));
    memset(extra, 0, sizeof(extra));
    while (cin >> x) {
      if (x == 0) break;
      if (x > 0)
        extra[x] = true;
      else
        miss[-x] = true;
    }
    cout << find_winner() + 1 << endl;
  }
  return 0;
}
