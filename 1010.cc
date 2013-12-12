#include <cstring>
#include <iostream>
using namespace std;

int n, x;
int val[100];
bool tie = false;

struct Solution {
  int num_types;
  int total;
  int type[4];
} best;

int max_value(Solution& s) {
  int ret = 0;
  for (int i = 0; i < s.total; i++)
    ret = max(ret, val[s.type[i]]);
  return ret;
}

void search(int pos, Solution& s, int sum) {
  if (sum == x) {
    if (best.total == -1) {
      tie = false;
      best = s;
    } else if (s.num_types > best.num_types) {
      tie = false;
      best = s;
    } else if (s.num_types == best.num_types) {
      if (s.total < best.total) {
        tie = false;
        best = s;
      } else if (s.total == best.total) {
        int max_s = max_value(s), max_best = max_value(best);
        if (max_s > max_best) {
          tie = false;
          best = s;
        } else if (max_s == max_best)
          tie = true;
      }
    }
    return;
  }
  if (s.total == 4 || pos == n) return;
  // Try to use current type.
  if (val[pos] <= x - sum) {
    bool old = s.total > 0 && s.type[s.total - 1] == pos;
    s.type[s.total++] = pos;
    s.num_types += !old;
    search(pos, s, sum + val[pos]);
    s.num_types -= !old;
    s.total--;
  }
  // Skip current type.
  search(pos + 1, s, sum);
}

int main() {
  while (cin >> x) {
    if (x == 0) {
      n = 0;
    } else {
      n = 1;
      val[0] = x;
      while (cin >> x) {
        if (x == 0) break;
        val[n++] = x;
      }
    }
    // Process each customer.
    while (cin >> x) {
      if (x == 0) break;
      best.total = -1;
      Solution s;
      memset(&s, 0, sizeof(s));
      search(0, s, 0);
      if (best.total == -1) {
        cout << x << " ---- none" << endl;
      } else {
        cout << x << " (" << best.num_types << "):";
        if (tie) {
          cout << " tie" << endl;
        } else {
          for (int i = 0; i < best.total; i++)
            cout << ' ' << val[best.type[i]];
          cout << endl;
        }
      }
    }
  }
  return 0;
}
