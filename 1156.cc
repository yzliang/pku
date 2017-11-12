#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
using namespace std;

const int MIN_HEIGHT = -30000;
const int MAX_HEIGHT = 30000;
int u, v, c;
int h[700][700];
// Records the max/min height of each row. They will be updated on the fly.
int max_h[700], min_h[700];

void ReadData() {
  scanf("%d %d %d", &u, &v, &c);
  for (int i = 0; i < v; ++i) {
    for (int j = 0; j < u; ++j) {
      scanf("%d", &h[i][j]);
    }
  }
}

// Queues for single pass algorithm.
struct HeightInfo {
  int row_id;
  int height;
} low_queue[1000], high_queue[1000];

// Algorithm: single pass + two queues.
// Complexity: O(V)
int ComputeRegion(int l_col, int r_col, int width) {
  int max_span = 0;
  int head_row = 0;
  // queue will be [low_head, low_tail).
  int low_head = 0, low_tail = 0;
  // queue will be [high_head, high_tail).
  int high_head = 0, high_tail = 0;
  for (int i = 0; i < v; ++i) {
    if (max_h[i] - min_h[i] > c) {
      low_head = low_tail = 0;
      high_head = high_tail = 0;
      head_row = i + 1;
      continue;
    }
    // Update header row according to max_h[i].
    while (low_head < low_tail && max_h[i] - low_queue[low_head].height > c) {
      head_row = low_queue[low_head++].row_id + 1;
    }
    while (high_head < high_tail && high_queue[high_head].row_id < head_row) {
      ++high_head;
    }
    // Update header row according to min_h[i].
    while (high_head < high_tail &&
        high_queue[high_head].height - min_h[i] > c) {
      head_row = high_queue[high_head++].row_id + 1;
    }
    while (low_head < low_tail && low_queue[low_head].row_id < head_row) {
      ++low_head;
    }
    // Keep monotonic queues.
    while (low_head < low_tail && low_queue[low_tail - 1].height > min_h[i]) {
      --low_tail;
    }
    while (high_head < high_tail &&
        high_queue[high_tail - 1].height < max_h[i]) {
      --high_tail;
    }
    // Now, insert max_h[i] and min_h[i] to queues.
    low_queue[low_tail].row_id = i;
    low_queue[low_tail++].height = min_h[i];
    high_queue[high_tail].row_id = i;
    high_queue[high_tail++].height = max_h[i];
    max_span = max(max_span, i - head_row + 1);
  }
  return max_span * width;
}

// Algorithm: enumeration.
// Complexity: U (left boundary) * 100 (width) * (V + ComputeRegion())
int Solve() {
  int ans = 0;
  for (int l_col = 0; l_col < u; ++l_col) {
    // Intialize max_h and min_h.
    for (int i = 0; i < v; ++i) {
      max_h[i] = MIN_HEIGHT;
      min_h[i] = MAX_HEIGHT;
    }
    for (int width = 1; width <= 100; ++width) {
      const int r_col = l_col + width - 1;
      if (r_col == u) break;
      // Update max_h and min_h.
      for (int i = 0; i < v; ++i) {
        max_h[i] = max(max_h[i], h[i][r_col]);
        min_h[i] = min(min_h[i], h[i][r_col]);
      }
      ans = max(ans, ComputeRegion(l_col, r_col, width));
    }
  }
  return ans;
}

int main() {
  ReadData();
  cout << Solve() << endl;
  return 0;
}
