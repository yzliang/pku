// Algorithm: rotate and compute.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> holes;

const int kHalf = 5000000;
const int kWhole = 10000000;

int ForwardDistance(int x, int y) {
  return x < y ? y - x : kWhole + y - x;
}

int BackwardDistance(int x, int y) {
  return x < y ? kWhole + x - y : x - y;
}

void Solve() {
  long long ans = -1;   // The final answer.
  long long total = 0;  // The current total time.

  // Initialze pivot to holes[0].
  sort(holes.begin(), holes.end());
  int fwd_index = 1;
  while (fwd_index < n && holes[fwd_index] - holes[0] <= kHalf) {
    total += ForwardDistance(holes[0], holes[fwd_index]);
    ++fwd_index;
  }
  for (int i = fwd_index; i < n; ++i) {
    total += BackwardDistance(holes[0], holes[i]);
  }
  ans = total;

  // Rotate the pivot to holes[1], ..., holes[n-1].
  int num_forward = fwd_index - 1;
  if (fwd_index == n) {
    fwd_index = 0;
  }
  for (int i = 1; i < n; ++i) {
    // Update distances for pivot shifting (p[i-1] -> p[i]).
    total -= num_forward * (holes[i] - holes[i - 1]);
    total += (n - num_forward) * (holes[i] - holes[i - 1]);
    // p[i] is now excluded from forward list.
    --num_forward;
    // Try to extend forward list.
    while (fwd_index != i &&
           ForwardDistance(holes[i], holes[fwd_index]) <= kHalf) {
      total -= BackwardDistance(holes[i], holes[fwd_index]);
      total += ForwardDistance(holes[i], holes[fwd_index]);
      ++num_forward;
      fwd_index = (fwd_index + 1) % n;
    }
    ans = min(ans, total);
  }
  cout << ans << endl;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int hole;
    cin >> hole;
    holes.push_back(hole);
  }
  Solve();
  return 0;
}
