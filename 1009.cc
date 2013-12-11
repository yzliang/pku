#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

struct Run {
  int val, len;
  Run() : val(0), len(0) {}
  Run(int val, int len) : val(val), len(len) {}
};

int width;
vector<Run> input;

bool read_input() {
  cin >> width;
  if (width == 0) return false;
  input.clear();
  Run run;
  while (cin >> run.val >> run.len) {
    if (run.len == 0) break;
    input.push_back(run);
  }
  return true;
}

void fill_row(vector<Run>& row, int& i, int& j) {
  int sum = 0;
  while (sum < width) {
    if (input[i].len - j <= width - sum) {
      row.push_back(Run(input[i].val, input[i].len - j));
      sum += input[i].len - j;
      i++;
      j = 0;
    } else {
      row.push_back(Run(input[i].val, width - sum));
      j += width - sum;
      break;
    }
  }
}

inline void append(vector<Run>& result, int val, int len) {
  if (len == 0) return;
  if (result.empty() || result.back().val != val)
    result.push_back(Run(val, len));
  else
    result.back().len += len;
}

inline void move(int& i, int& j, int len, int delta) {
  j += delta;
  if (j == len) {
    i++;
    j = 0;
  }
}

void produce(vector<Run>& result, vector<Run>& upper, vector<Run>& middle,
    vector<Run>& lower) {
  int i1 = 0, i2 = 0, i3 = 0;
  int pos1 = 0, pos2 = 0, pos3 = 0;
  while (i2 < middle.size()) {
    int len = min(min(upper[i1].len - pos1, middle[i2].len - pos2),
        lower[i3].len - pos3);
    // Append new computed runs.
    int val = max(abs(middle[i2].val - upper[i1].val),
        abs(middle[i2].val - lower[i3].val));
    int lval = val, rval = val;
    if (pos1 == 0 && i1 > 0)
      lval = max(lval, abs(middle[i2].val - upper[i1 - 1].val));
    if (pos2 == 0 && i2 > 0)
      lval = max(lval, abs(middle[i2].val - middle[i2 - 1].val));
    if (pos3 == 0 && i3 > 0)
      lval = max(lval, abs(middle[i2].val - lower[i3 - 1].val));
    if (pos1 + len == upper[i1].len && i1 + 1 < upper.size())
      rval = max(rval, abs(middle[i2].val - upper[i1 + 1].val));
    if (pos2 + len == middle[i2].len && i2 + 1 < middle.size())
      rval = max(rval, abs(middle[i2].val - middle[i2 + 1].val));
    if (pos3 + len == lower[i3].len && i3 + 1 < lower.size())
      rval = max(rval, abs(middle[i2].val - lower[i3 + 1].val));
    if (len == 1)
      append(result, max(lval, rval), 1);
    else {
      append(result, lval, 1);
      append(result, val, len - 2);
      append(result, rval, 1);
    }
    move(i1, pos1, upper[i1].len, len);
    move(i2, pos2, middle[i2].len, len);
    move(i3, pos3, lower[i3].len, len);
  }
}

void compute(vector<Run>& result) {
  vector<Run> upper, middle, lower;
  int i = 0, j = 0;
  fill_row(upper, i, j);
  middle = upper;
  while (i < input.size()) {
    if (upper.size() == 1 && middle.size() == 1 &&
        upper[0].val == input[i].val && middle[0].val == input[i].val &&
        input[i].len - j >= width) {
      int len = width * ((input[i].len - j) / width);
      append(result, 0, len);
      j += len;
      if (j == input[i].len) {
        j = 0;
        i++;
      }
    } else {
      fill_row(lower, i, j);
      produce(result, upper, middle, lower);
      upper.swap(middle);
      middle.swap(lower);
      lower.clear();
    }
  }
  lower = middle;
  produce(result, upper, middle, lower);
}

int main() {
  while (read_input()) {
    vector<Run> result;
    compute(result);
    cout << width << endl;
    for (int i = 0; i < result.size(); i++)
      cout << result[i].val << ' ' << result[i].len << endl;
    cout << "0 0" << endl;
  }
  cout << 0 << endl;
  return 0;
}
