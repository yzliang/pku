/*
 * Inverse Burrows-Wheeler transformation.
 *
 * Input:
 *   string s, the last column of the sorted rotation table.
 *
 * Algorithm:
 *   repeatedly insert s as the first column, sort rows of the table
 *   alphabetically. 
 *
 * Optimization hint in the implementation:
 *   since we only need the first row from the resulted table, there is no
 *   need to sort and store the entire table. The following solution just
 *   recovers the first row by tracking the index of its suffix among all rows'
 *   suffixes.
 */
#include <iostream>
using namespace std;

int n, num_zeros, num_ones;
int zero_idx[3000], one_idx[3000];

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (x == 0) {
      zero_idx[num_zeros++] = i;
    } else {
      one_idx[num_ones++] = i;
    }
  }

  if (n == 0) {
    cout << endl;
    return 0;
  }

  int value = num_zeros > 0 ? 0 : 1;
  int index = num_zeros > 0 ? zero_idx[0] : one_idx[0];
  cout << value;

  for (int i = 1; i < n; i++) {
    // Find the next column.
    if (index < num_zeros) {
      value = 0;
      index = zero_idx[index];
    } else {
      value = 1;
      index = one_idx[index - num_zeros];
    }
    cout << ' ' << value;
  }
  cout << endl;
  return 0;
}
