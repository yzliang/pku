#include <climits>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;

int min_cost, max_cost, n, m;
int cost[20], needs[20], sales[20];
int best_sales, best_cost, best_num_features, best_num_customers,
    best_customers, best_features;
int best_index;

void dump_bits(int x, int total) {
  bool first = true;
  for (int j = 0; j < total; j++) {
    if (x & (1 << j)) {
      if (first)
        first = false;
      else
        cout << ' ';
      cout << j + 1;
    }
  }
  cout << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cin >> min_cost >> max_cost >> n >> m;
    best_index = INT_MIN;
    for (int j = 0; j < n; j++)
      cin >> cost[j];
    for (int j = 0; j < m; j++) {
      int total;
      cin >> total;
      needs[j] = 0;
      for (int k = 0; k < total; k++) {
        int id;
        cin >> id;
        needs[j] |= (1 << (id - 1));
      }
      cin >> sales[j];
    }
    // Enumerate the feature set.
    for (int features = 0; features < (1 << n); features++) {
      int total_cost = 0, num_features = 0;
      for (int j = 0; j < n; j++) {
        if (features & (1 << j)) {
          total_cost += cost[j];
          num_features++;
        }
      }
      if (total_cost < min_cost || total_cost > max_cost)
        continue;
      int total_sales = 0, num_customers = 0, customers = 0;
      for (int j = 0; j < m; j++) {
        if ((features | needs[j]) == features) {
          total_sales += sales[j];
          num_customers++;
          customers |= (1 << j);
        }
      }
      int index = round((double) total_sales / total_cost * 1000);
      bool update = false;
      if (index > best_index)
        update = true;
      else if (index == best_index) {
        if (total_sales - total_cost > best_sales - best_cost)
          update = true;
        else if (best_sales - best_cost == total_sales - total_cost) {
          if (num_features < best_num_features)
            update = true;
          else if (num_features == best_num_features) {
            if (num_customers > best_num_customers)
              update = true;
          }
        }
      }
      if (update) {
        best_index = index;
        best_sales = total_sales;
        best_cost = total_cost;
        best_num_features = num_features;
        best_num_customers = num_customers;
        best_customers = customers;
        best_features = features;
      }
    }
    cout << "Feature Set " << i << endl;
    cout << fixed << setprecision(3) << best_index / 1000.0 << endl;
    cout << best_sales << endl << best_cost << endl;
    dump_bits(best_features, n);
    dump_bits(best_customers, m);
  }
  return 0;
}
