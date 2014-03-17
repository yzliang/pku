#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

// Order for sticks.
struct Order {
  int id, num;
  bool operator<(const Order& that) const {
    if (num != that.num)
      return num > that.num;
    else
      return id < that.id;
  }
};

int n, k, num_sticks, ans, rest_squares;
bool removed[60];
Order order[60];
int rest_by_edge[6];
int num_edges[55], total_sticks[55], rest_sticks[55];
vector<vector<int> > squares, sticks;

int get_stick_id(int r, int c, int left) {
  if (left == 0)
    return r * n + r * (n + 1) + c;
  else
    return (r + 1) * n + r * (n + 1) + c;
}

void build_map() {
  num_sticks = 2 * n * (n + 1);
  sticks.resize(num_sticks);
  for (int i = 0; i < num_sticks; i++)
    sticks[i].clear();
  squares.clear();
  memset(rest_by_edge, 0, sizeof(rest_by_edge));
  for (int len = n; len >= 1; len--) {
    for (int x = 0; x <= n - len; x++) {
      for (int y = 0; y <= n - len; y++) {
        int square_id = squares.size();
        num_edges[square_id] = len;
        rest_by_edge[len]++;
        total_sticks[square_id] = rest_sticks[square_id] = len * 4;
        squares.push_back(vector<int>());
        for (int i = 0; i < len; i++) {
          int id = get_stick_id(x, y + i, 0);
          squares.back().push_back(id);
          sticks[id].push_back(square_id);
          id = get_stick_id(x + i, y, 1);
          squares.back().push_back(id);
          sticks[id].push_back(square_id);
          id = get_stick_id(x + len, y + i, 0);
          squares.back().push_back(id);
          sticks[id].push_back(square_id);
          id = get_stick_id(x + i, y + len, 1);
          squares.back().push_back(id);
          sticks[id].push_back(square_id);
        }
      }
    }
  }
  // Mark the change made by removed sticks.
  rest_squares = squares.size();
  for (int i = 0; i < num_sticks; i++) {
    if (!removed[i]) continue;
    for (int j = 0; j < sticks[i].size(); j++) {
      int id = sticks[i][j];
      if (rest_sticks[id] == total_sticks[id]) {
        rest_squares--;
        rest_by_edge[num_edges[id]]--;
      }
      rest_sticks[id]--;
    }
  }
}

void reorder() {
  for (int i = 0; i < num_sticks; i++) {
    order[i].id = i;
    order[i].num = 0;
    for (int j = 0; j < sticks[i].size(); j++) {
      int id = sticks[i][j];
      if (rest_sticks[id] == total_sticks[id])
        order[i].num++;
    }
  }
  sort(order, order + num_sticks);
}

void search(int p, int num_removed, int rest) {
  if (p == num_sticks) {
    if (rest == 0)
      ans = min(ans, num_removed);
    return;
  }
  int k = order[p].id;
  if (removed[k]) search(p + 1, num_removed, rest);
  // Pruning: compute the least number of sticks need to remove.
  int need = 0;
  for (int i = 1; i <= n; i++)
    need = max(need, (rest_by_edge[i] + 1) / 2);
  if (num_removed + need >= ans) return;
  if (num_sticks - p < need) return;
  // Remove k?
  removed[k] = true;
  for (int i = 0; i < sticks[k].size(); i++) {
    int id = sticks[k][i];
    if (total_sticks[id] == rest_sticks[id]) {
      rest--;
      rest_by_edge[num_edges[id]]--;
    }
    rest_sticks[id]--;
  }
  search(p + 1, num_removed + 1, rest);
  // Backtracking.
  removed[k] = false;
  for (int i = 0; i < sticks[k].size(); i++) {
    int id = sticks[k][i];
    rest_sticks[id]++;
    if (total_sticks[id] == rest_sticks[id]) {
      rest++;
      rest_by_edge[num_edges[id]]++;
    }
  }
  // Don't use k?
  search(p + 1, num_removed, rest);
}

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    cin >> n;
    cin >> k;
    memset(removed, 0, sizeof(removed));
    for (int i = 0; i < k; i++) {
      int x;
      cin >> x;
      removed[x - 1] = true;
    }
    build_map();
    reorder();
    ans = num_sticks - k;
    search(0, 0, rest_squares);
    cout << ans << endl;
  }
  return 0;
}
