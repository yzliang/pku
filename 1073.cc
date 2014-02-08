#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Link {
  int l, r, y;
  bool used;
  bool operator<(const Link& that) const {
    return y < that.y;
  }
};

struct Pipe {
  int x, y, h;
};

int p, l, ans, next_id;
int sp, sh;  // spider's pipe and height.
bool die, stop;
Pipe pipes[20];
Link links[50];
int size[20];  // size of each group.
int group[20];  // group id of pipes.
int water[20];  // water level of each group.
int bounds[20];  // group bound.

void fill(int g, int bound) {
  while (!die && !stop) {
    // Find the lowest link.
    int np = -1, nh = -1;
    for (int i = l - 1; i >= 0; i--) {
      if (links[i].used) continue;
      if (group[links[i].l] == g && group[links[i].r] == -1) {
        if (links[i].y < bound) break;
        np = links[i].r;
        nh = links[i].y;
        links[i].used = true;
        break;
      }
      if (group[links[i].r] == g && group[links[i].l] == -1) {
        if (links[i].y < bound) break;
        np = links[i].l;
        nh = links[i].y;
        links[i].used = true;
        break;
      }
    }
    // No more out-links ?
    if (np == -1) {
      // Dying ?
      if (group[sp] == g && sh > bounds[g] && sh > bound) {
        ans += size[g] * (water[g] - sh);
        die = true;
        return;
      }
      // Stopping ?
      if (bounds[g] > bound) {
        stop = true;
        return;
      }
      // Fill to bound.
      ans += size[g] * (water[g] - bound);
      water[g] = bound;
      return;
    }
    // Fill this group to the link level.
    // Dying ?
    if (group[sp] == g && sh > nh && sh > bounds[g]) {
      ans += size[g] * (water[g] - sh);
      die = true;
      return;
    }
    // Stopping ?
    if (bounds[g] > nh) {
      stop = true;
      return;
    }
    ans += size[g] * (water[g] - nh);
    water[g] = nh;
    // Add and fill the newly linked group.
    group[np] = next_id++;
    size[group[np]] = 1;
    water[group[np]] = pipes[np].y + pipes[np].h;
    bounds[group[np]] = pipes[np].y;
    fill(group[np], nh);
    // Group merge.
    int old = group[np];
    size[g] += size[old];
    bounds[g] = max(bounds[g], bounds[old]);
    for (int i = 0; i < p; i++)
      if (group[i] == old) group[i] = g;
    // Dying ?
    if (sh == nh && sh > bounds[g]) {
      die = true;
      return;
    }
  }
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    // Load and connect.
    cin >> p;
    for (int i = 0; i < p; i++)
      cin >> pipes[i].x >> pipes[i].y >> pipes[i].h;
    cin >> l;
    for (int i = 0; i < l; i++) {
      int x, y, len, lp, rp;
      cin >> x >> y >> len;
      for (int j = 0; j < p; j++) {
        if (y >= pipes[j].y && y <= pipes[j].y + pipes[j].h) {
          if (x == pipes[j].x + 1)
            links[i].l = j;
          else if (x + len == pipes[j].x)
            links[i].r = j;
        }
      }
      links[i].y = y;
      links[i].used = false;
    }
    sort(links, links + l);
    cin >> sp >> sh;
    sp--;
    if (!(sh > pipes[sp].y && sh <= pipes[sp].y + pipes[sp].h)) {
      cout << "No Solution" << endl;
      continue;
    }
    // Init.
    die = stop = false;
    ans = 0;
    for (int i = 0; i < p; i++)
      group[i] = -1;
    // Set up group 0.
    group[0] = 0;
    size[0] = 1;
    water[0] = pipes[0].y + pipes[0].h;
    bounds[0] = pipes[0].y;
    next_id = 1;
    fill(0, pipes[0].y);
    if (die)
      cout << ans << endl;
    else
      cout << "No Solution" << endl;
  }
  return 0;
}
