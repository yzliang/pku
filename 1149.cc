#include <algorithm>
#include <iostream>
using namespace std;

const int kMaxNodes = 1000 + 100 + 2;
const int kFlowLimit = 10000000;

int n, m;
int source, sink;
int cap[kMaxNodes][kMaxNodes];  // network capacity (intialized to zero)

int ComputeMaxFlow() {
  int ans = 0;
  while (true) {
    // Find the augmenting path with highest capacity from source to sink.
    int prev_node[kMaxNodes] = {0};
    int max_cap[kMaxNodes] = {0};
    max_cap[source] = kFlowLimit;
    bool visit[kMaxNodes] = {0};
    while (true) {
      int cur_max_cap = 0;
      int cur_node = -1;
      for (int i = 0; i < n + m + 2; i++) {
        if (!visit[i] && max_cap[i] > cur_max_cap) {
          cur_max_cap = max_cap[i];
          cur_node = i;
        }
      }
      if (cur_node == -1 || cur_node == sink)
        break;
      visit[cur_node] = true;
      for (int i = 0; i < n + m + 2; i++) {
        if (max_cap[i] < min(cur_max_cap, cap[cur_node][i])) {
          max_cap[i] = min(cur_max_cap, cap[cur_node][i]);
          prev_node[i] = cur_node;
        }
      }
    }
    if (max_cap[sink] == 0)
      break;  // No more augmenting path.
    ans += max_cap[sink];
    for (int i = sink; i != 0; i = prev_node[i]) {
      cap[prev_node[i]][i] -= max_cap[sink];
      cap[i][prev_node[i]] += max_cap[sink];
    }
  }
  return ans;
}

int main() {
  // Read input and build graph.
  cin >> m >> n;
  source = 0;
  sink = m + n + 1;
  for (int i = 1; i <= m; i++) {
    cin >> cap[0][i];
  }
  int last_customer[1001] = {0};  // last customer for each house
  for (int i = 1; i <= n; i++) {
    int num_houses;
    cin >> num_houses;
    for (int j = 0; j < num_houses; j++) {
      int house;
      cin >> house;
      if (last_customer[house] == 0) {
        cap[house][m + i] = kFlowLimit;
      } else {
        cap[m + last_customer[house]][m + i] = kFlowLimit;
      }
      last_customer[house] = i;
    }
    int demand;
    cin >> demand;
    cap[m + i][m + n + 1] = demand;
  }

  cout << ComputeMaxFlow() << endl;

  return 0;
}
