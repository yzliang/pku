#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

struct Student {
  int r, m, k, next, result;
  int fdus[50];
} s[151];

struct FDU {
  int r, c;
  int s, next;  // Number of students and the next student.
  int ids[150];  // Student ids.
} f[51];

struct Comparator {
  int fdu;
  Comparator(int fdu): fdu(fdu) {}
  bool operator()(int s1, int s2) {
    if ((s[s1].r == f[fdu].r) ^ (s[s2].r == f[fdu].r)) {
      if (s[s1].r == f[fdu].r)
        return 10 * s[s1].m > 7 * s[s2].m;
      else
        return 7 * s[s1].m >= 10 * s[s2].m;
    } else
      return s[s1].m > s[s2].m;
  }
};

int n, m;

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> n >> m;
    memset(s, 0, sizeof(s));
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) {
      cin >> s[i].r >> s[i].m >> s[i].k;
      for (int j = 0; j < s[i].k; j++) {
        int fdu;
        cin >> fdu;
        s[i].fdus[j] = fdu;
        f[fdu].ids[f[fdu].s++] = i;
      }
      s[i].result = -1;
    }
    for (int i = 1; i <= m; i++) {
      cin >> f[i].r >> f[i].c;
      // Sort students applied to this FDU.
      sort(f[i].ids, f[i].ids + f[i].s, Comparator(i));
    }
    while (true) {
      bool found = false;
      for (int i = 1; i <= m; i++) {
        if (f[i].c == 0) continue;
        // Find the first student whoese top preference is this FDU.
        while (f[i].next < f[i].s && s[f[i].ids[f[i].next]].result != -1)
          f[i].next++;
        if (f[i].next == f[i].s) continue;
        for (int j = f[i].next; j < f[i].s; j++) {
          int id = f[i].ids[j];
          if (s[id].result != -1) continue;
          // Get the student's top preference.
          while (true) {
            int fdu = s[id].fdus[s[id].next];
            if (f[fdu].c == 0)
              s[id].next++;
            else
              break;
          }
          if (i != s[id].fdus[s[id].next]) continue;
          // Match!
          found = true;
          s[id].result = i;
          f[i].c--;
          break;
        }
      }
      if (!found) break;
    };
    for (int i = 1; i <= n; i++) {
      if (s[i].result == -1)
        cout << "not accepted" << endl;
      else
        cout << s[i].result << endl;
    }
    if (t > 1) cout << endl;
  }
  return 0;
}
