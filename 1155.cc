// Dynamic programming with O(n^3) worst case.
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int> > graph;

struct Node {
  int num_users;
  int lc, rc;  // children
  int cost;   // cost from parent to the node.

  Node() {
    lc = rc = num_users = 0;
  }
};
vector<Node> nodes;

vector<vector<int> > cost;
vector<int> gain;
// f[i][j]: max earning on transmitter i with j users selected.
vector<vector<int> > f;

void Read() {
  cin >> n >> m;
  graph.resize(n + 1);
  cost.resize(n - m + 1);
  for (int i = 1; i <= n - m; ++i) {
    int k;
    cin >> k;
    graph[i].resize(k);
    cost[i].resize(k);
    for (int j = 0; j < k; ++j) {
      cin >> graph[i][j] >> cost[i][j];
    }
  }
  gain.resize(n + 1);
  for (int i = n - m + 1; i <= n; ++i) {
    cin >> gain[i];
  }
}

void BuildBinaryTree(int i) {
  for (int j = 0; j < graph[i].size(); ++j) {
    if (j == 0) {
      nodes[i].lc = graph[i][0];
      nodes[graph[i][0]].cost = cost[i][0];
    } else {
      nodes[graph[i][j - 1]].rc = graph[i][j];
      nodes[graph[i][j]].cost = cost[i][j];
    }
    BuildBinaryTree(graph[i][j]);
  }
}

void CountUsers(int i) {
  if (nodes[i].lc > 0) {
    CountUsers(nodes[i].lc);
  }
  if (nodes[i].rc > 0) {
    CountUsers(nodes[i].rc);
  }
  nodes[i].num_users = (i > n - m) + nodes[nodes[i].lc].num_users +
                       nodes[nodes[i].rc].num_users;
}

// DP state: node i with j users.
void Compute(int i, int j) {
  if (f[i][j] != INT_MIN)
    return;
  if (nodes[i].lc == 0) {
    // node i is a user node.
    // option 1: pick user i
    int left_gain = gain[i] - nodes[i].cost;
    int right_gain = 0;
    if (nodes[i].rc > 0) {
      Compute(nodes[i].rc, j - 1);
      right_gain = f[nodes[i].rc][j - 1];
    }
    if (left_gain + right_gain > f[i][j]) {
      f[i][j] = left_gain + right_gain;
    }
    // option 2: don't pick user i.
    if (nodes[i].rc > 0 && nodes[nodes[i].rc].num_users >= j) {
      Compute(nodes[i].rc, j);
      if (f[nodes[i].rc][j] > f[i][j]) {
        f[i][j] = f[nodes[i].rc][j];
      }
    }
  } else {
    // node i is a transmitter node.
    for (int k = 0; k <= nodes[nodes[i].lc].num_users; ++k) {
      // when we take k users from lc, there must exist at least j - k users
      // from rc.
      int num_rc_users = nodes[i].rc > 0 ? nodes[nodes[i].rc].num_users : 0;
      if (j - k > num_rc_users) {
        continue;
      }
      int left_gain = 0;
      if (k > 0) {
        Compute(nodes[i].lc, k);
        left_gain = f[nodes[i].lc][k] - nodes[i].cost;
      }
      int right_gain = 0;
      if (j - k > 0) {
        Compute(nodes[i].rc, j - k);
        right_gain = f[nodes[i].rc][j - k];
      }
      if (left_gain + right_gain > f[i][j]) {
        f[i][j] = left_gain + right_gain;
      }
    }
  }
}

void Solve() {
  // Turn the tree into left-child-right-sibling representation.
  nodes.resize(n + 1);
  BuildBinaryTree(1);
  CountUsers(1);

  // Init.
  f.resize(n + 1);
  for (int i = 1; i <= n; ++i) {
    f[i].resize(nodes[i].num_users + 1, INT_MIN);
    f[i][0] = 0;
  }

  // Compute (1, m), ..., (1, 1).
  for (int i = m; i >= 0; --i) {
    Compute(1, i);
    if (f[1][i] >= 0) {
      cout << i << endl;
      return;
    }
  }
}

int main() {
  Read();
  Solve();
  return 0;
}
