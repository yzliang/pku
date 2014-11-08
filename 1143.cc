#include <iostream>
using namespace std;

int n;
int win[1048576];

int set(int s, int i) {
  return s | (1 << i);
}

bool is_set(int s, int i) {
  return s & (1 << i);
}

int clear(int s, int i) {
  return s & (~(1 << i));
}

int select(int s, int a) {
  int ns = s;
  // Remove a's multiples.
  for (int i = a; i <= 20; i += a)
    ns = clear(ns, i - 1);
  // Remove i = a*x + b*y
  for (int i = 2; i <= 20; i++) {
    if (is_set(ns, i - 1)) {
      for (int j = a; i - j > 1; j += a) {
        if (!is_set(ns, i - j - 1)) {
          ns = clear(ns, i - 1);
          break;
        }
      }
    }
  }
  return ns;
}

int compute(int s) {
  if (win[s] != -1)
    return win[s];
  // Try every move.
  for (int i = 2; i <= 20; i++) {
    if (is_set(s, i - 1) && compute(select(s, i)) == 0)
      return win[s] = 1;
  }
  return win[s] = 0;
}

int main() {
  for (int i = 0; i < 1048576; i++)
    win[i] = -1;
  win[0] = 0;
  int id = 1;
  while (cin >> n) {
    if (n == 0)
      break;
    int s = 0;
    for (int i = 0; i < n; i++) {
      int a;
      cin >> a;
      s = set(s, a - 1);
    }
    cout << "Test Case #" << id++ << endl;
    if (compute(s) == 0)
      cout << "There's no winning move." << endl;
    else {
      cout << "The winning moves are:";
      for (int i = 2; i <= 20; i++) {
        if (is_set(s, i - 1) && compute(select(s, i)) == 0)
          cout << ' ' << i;
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
