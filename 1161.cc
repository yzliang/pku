#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int m, n, l;
int members[251];

// border[i][j] denotes the region that contains border town_i->town_j.
int border[251][251];

vector<int> town_regions[251];
bool region_connects[201][201];
int dis[201][201];

void ReadData() {
  cin >> m >> n >> l;
  for (int i = 0; i < l; ++i) {
    cin >> members[i];
  }
  for (int i = 1; i <= m; ++i) {
    int num_towns, first_town, prev_town = -1, current_town;
    cin >> num_towns;
    for (int j = 0; j < num_towns; ++j) {
      if (j == 0) {
        cin >> first_town;
        current_town = first_town;
      } else {
        cin >> current_town;
        border[prev_town][current_town] = i;
      }
      town_regions[current_town].push_back(i);
      prev_town = current_town;
    }
    border[current_town][first_town] = i;
  }
}

void BuildRegionGraph() {
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (border[i][j] > 0) {
        int r1 = border[i][j], r2 = border[j][i];
        region_connects[r1][r2] = region_connects[r2][r1] = true;
      }
    }
  }
}

void Floyd() {
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (i != j) {
        dis[i][j] = region_connects[i][j] ? 1 : INT_MAX;
      }
    }
  }
  for (int k = 1; k <= m; ++k) {
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (i != j && dis[i][k] != INT_MAX && dis[k][j] != INT_MAX) {
          dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        }
      }
    }
  }
}

int Solve() {
  BuildRegionGraph();
  Floyd();
  int ans = INT_MAX;
  for (int i = 1; i <= m; ++i) {
    int sum_dis = 0;
    for (int j = 0; j < l; ++j) {
      int town = members[j];
      int min_dis = INT_MAX;
      for (size_t k = 0; k < town_regions[town].size(); ++k) {
        int region = town_regions[town][k];
        min_dis = min(min_dis, dis[i][region]);
      }
      sum_dis += min_dis;
    }
    ans = min(ans, sum_dis);
  }
  return ans;
}

int main() {
  ReadData();
  cout << Solve() << endl;
  return 0;
}
