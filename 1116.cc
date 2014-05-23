#include <algorithm>
#include <iostream>
using namespace std;

struct Shelf {
  int y, l, x, p1, p2;
};

int nh, nw, th, tw, n, lower, min_pegs, min_len;
Shelf s[100];

bool compare_height(const Shelf& s1, const Shelf& s2) {
  return s1.y > s2.y;
}

// Compute the max offset to the left.
int delta_left(const Shelf& s) {
  int delta = min(s.x, s.x + s.l - s.p2);
  return min(delta, (int) (s.x + s.l / 2.0 - s.p1));
}

// Compute the max offset to the right.
int delta_right(const Shelf& s) {
  int delta = min(nw - s.x - s.l, s.p1 - s.x);
  return min(delta, (int) (s.p2 - s.x - s.l / 2.0));
}

void adjust_shelf(int tx, int ty, const Shelf& s, int& pegs, int& len) {
  // Non-overlapping?
  if (s.x + s.l <= tx || s.x >= tx + tw)
    return;
  if (s.p2 <= tx) {  // Two pegs on the left?
    int max_len = min(tx, (tx - s.p1) * 2);
    if (s.l > max_len)
      len += s.l - max_len;
  } else if (s.p1 >= tx + tw) {  // Two pegs on the right?
    int max_len = min(nw - tx - tw, (s.p2 - tx - tw) * 2);
    if (s.l > max_len)
      len += s.l - max_len;
  } else if (s.p1 <= tx && s.p2 < tx + tw) {
    // The right peg is in the tome?
    if (tx == 0) {  // No space to relocate the peg?
      // Remove all.
      pegs += 2;  
      len += s.l;
      return;
    }
    pegs++;
    if (tx < s.l)
      len += s.l - tx;
  } else if (s.p2 >= tx + tw && s.p1 > tx) {
    // The left peg is in the tome?
    if (tx + tw == nw) {  // No space to relocate the peg?
      // Remove all.
      pegs += 2;
      len += s.l;
      return;
    }
    pegs++;
    if (nw - tx - tw < s.l)
      len += s.l - (nw - tx - tw);
  } else if (s.p1 > tx && s.p2 < tx + tw) {  // Both pegs in the tome?
    pegs += 2;
    len += s.l;
  } else {  // Two pegs on both sides.
    pegs++;
    int gap1 = tx, gap2 = nw - tx - tw;
    if (gap1 >= s.l || gap2 >= s.l)
      return;
    if (gap1 == 0 && gap2 == 0) {
      pegs++;  // No space.
      len += s.l;
      return;
    }
    if (gap1 == 0 || (gap2 != 0 && gap1 > gap2))
      len += s.l - gap2;
    else
      len += s.l - gap1;
  }
}

// Compute the min pegs and lengths given the lower-left corner of the tome.
void compute(int tx, int ty, int p, int q, int pegs) {
  bool moved = pegs == 1;
  int len = 0;
  for (int i = p; i < q; i++) {
    adjust_shelf(tx, ty, s[i], pegs, len);
    if (pegs > min_pegs || (pegs == min_pegs && len >= min_len))
      return;
  }
  min_pegs = pegs;
  min_len = len;
}

int main() {
  cin >> nw >> nh >> tw >> th >> n;
  for (int i = 0; i < n; i++) {
    cin >> s[i].y >> s[i].x >> s[i].l >> s[i].p1 >> s[i].p2;
    s[i].p1 += s[i].x;
    s[i].p2 += s[i].x;
  }
  sort(s, s + n, compare_height);
  min_pegs = 200;
  for (int i = 0; i < n; i++) {  // Enumerate the base shelf.
    if (s[i].l < tw || s[i].y + th > nh)
      continue;
    // Locate the highest shelf that may be an obstacle.
    while (lower < i && s[i].y + th <= s[lower].y)
      lower++;
    // No peg is removed.
    int delta_l = delta_left(s[i]);
    int delta_r = delta_right(s[i]);
    int l1 = s[i].x - delta_l, r1 = s[i].x + s[i].l + delta_r;
    for (int j = l1; j + tw <= r1; j++)
      compute(j, s[i].y, lower, i, 0);
    // If one peg is removed.
    int l2 = max(0, s[i].p1 - s[i].l);
    int r2 = min(nw, s[i].p2 + s[i].l);
    for (int j = l2; j + tw <= r2; j++) {
      if (j < l1 || j + tw > r1)
        compute(j, s[i].y, lower, i, 1);
    }
  }
  cout << min_pegs << ' ' << min_len << endl;
  return 0;
}
